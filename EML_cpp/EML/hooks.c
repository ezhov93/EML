/*
 * @file  ehook.c
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Empty yield() hook.
 */

static void __empty() {
	// empty
}
void yield(void) __attribute__ ((weak, alias("__empty")));
