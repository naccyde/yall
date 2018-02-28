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

#include "writer/test_writer.h"

#include "yall/writer/syslog.h"

Test(writer_syslog, test_str_to_syslog_facility0)
{
	cr_assert_eq(str_to_syslog_facility("yall_fac_user"), yall_fac_user);
	cr_assert_eq(str_to_syslog_facility("invalid"), yall_fac_user);
	cr_assert_eq(str_to_syslog_facility("yall_fac_kern"), yall_fac_kern);
	cr_assert_eq(str_to_syslog_facility("yall_fac_inherited"), yall_fac_inherited);
	cr_assert_eq(str_to_syslog_facility("yall_fac_local1"), yall_fac_local1);
}
