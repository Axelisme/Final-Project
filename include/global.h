#ifndef GLOBAL_H
#define GLOBAL_H

#define STR_(X) #X
#define STR(X) STR_(X)

#define FONT_PATH data/fonts
#define IMAGE_PATH data/Image

#define Debug 1

enum ERR_MSG {
    INIT_FAIL,
    START_FAIL,
    RUNTIME_FAIL,
    KEY_TERNIMATE
};


#endif // GLOBAL_H