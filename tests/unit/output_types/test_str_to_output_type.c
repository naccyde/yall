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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "test_output_types.h"

/*
 * Valid output type
 */
Test(log_level, test_str_to_output_types0)
{
	cr_assert_eq(yall_console_output, str_to_output_type("yall_console_output"));
	cr_assert_eq(yall_file_output, str_to_output_type("yall_file_output"));
	cr_assert_eq(yall_syslog_output, str_to_output_type("yall_syslog_output"));
}

/*
 * Invalid output type
 */
Test(log_level, test_str_to_output_types1)
{
	cr_assert_eq(yall_console_output, str_to_output_type(NULL));
	cr_assert_eq(yall_console_output, str_to_output_type("invalid"));
}