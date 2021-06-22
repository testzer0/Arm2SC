#define ASSERT(stmt) __CPROVER_assert(stmt, "Assert error")

int main()
{
	int a = 12;
	ASSERT(__builtin_ctz(a) == 2);
	return 0;
}