/*
 * MIT License
 *
 * Copyright (c) 2017 Quentin "Naccyde" Deslandes.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "yall/writer/thread.h"

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "yall/errors.h"
#include "yall/queue.h"
#include "yall/output_types.h"
#include "yall/message.h"

/*
 * This should ensure atomicity of read / write on the variable. But, as
 * Chris Hanson mention here https://stackoverflow.com/questions/78277/how-to-guarantee-64-bit-writes-are-atomic,
 * there is many factors to check to be sure this will work. So, this is
 * not sufficient, but... This variable is not business critical.
 * Also, Intel assumes reading / writing a 64 bits aligned variable is 
 * thread safe : https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf
 * See also : http://preshing.com/20130618/atomic-vs-non-atomic-operations/
 */
static __declspec(align(64)) bool thread_run = true;

static uint16_t frequency;
static pthread_t thread;
static void *writer_thread_routine(void *args);

uint8_t start_thread(uint16_t f)
{
	int ret = YALL_OK;

	frequency = f;

	int thread_ret = pthread_create(&thread, NULL, writer_thread_routine, NULL);

	if (thread_ret != 0) {
		ret = YALL_CANT_CREATE_THREAD;
		goto end;
	}

end:
	return ret;
}

void stop_thread(void)
{
	thread_run = false;
	pthread_join(thread, NULL);
}

static void write_queue(struct qnode *msg_queue)
{
	if (! msg_queue)
		return;

	write_queue(msg_queue->next);

	struct message *m = msg_queue->data;
	if (yall_console_output & m->output_type)
		write_log_console(m->log_level, m->data);

	if (yall_file_output & m->output_type)
		write_log_file(m->output_file, m->data);

	qnode_delete(msg_queue, message_delete);
}

static void *writer_thread_routine(void *args)
{
	double loop_duration_ms = (1.0 / frequency) * 1000.0;

	while (thread_run) {
		clock_t begin = clock();

		struct qnode *msg_queue = swap_queue();

		write_queue(msg_queue);

		int wait_ms = loop_duration_ms - ((clock() - begin) / CLOCKS_PER_SEC) * 1000.0;
		Sleep(wait_ms);
	}

	printf("Thread stopped\n");
}