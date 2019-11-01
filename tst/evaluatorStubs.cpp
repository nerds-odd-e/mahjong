#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "../mahjong_evaluator/include/mj_evaluator.h"

int LIB_evaluator_evaluate_array(mahjong_evaluator_handle_t handle, tile_t tiles[],
		int array_size) {
	FAIL("LIB_evaluator_evaluate_array HAS BEEN CALLED!");
	return 0;
}
mahjong_evaluator_handle_t LIB_create_evaluator(void) {
	FAIL("LIB_create_evaluator HAS BEEN CALLED!");
	return 0;
}
void LIB_evaluator_destroy(mahjong_evaluator_handle_t handle) {
	FAIL("LIB_evaluator_destroy HAS BEEN CALLED!");
}

