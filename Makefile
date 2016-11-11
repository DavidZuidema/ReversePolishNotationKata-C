check: convert-rpn_test.c
	gcc convert-rpn_test.c `pkg-config --cflags --libs check` -o convert-rpn && ./convert-rpn
