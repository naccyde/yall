#include <criterion/criterion.h>
#include <stdbool.h>
#include "yall/yall.h"
#include "yall/errors.h"
#include "h_stream.h"

extern bool initialized;

Test(subsystem, test_yall_init0)
{
	cr_assert_eq(yall_init(), YALL_OK);
	cr_assert_eq(initialized, true);
	cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
}
