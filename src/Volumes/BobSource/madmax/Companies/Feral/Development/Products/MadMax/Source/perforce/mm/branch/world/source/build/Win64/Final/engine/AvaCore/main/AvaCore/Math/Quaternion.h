#ifndef ENGINE_QUATERNION_H
#define ENGINE_QUATERNION_H

class CQuaternion {
    union {
        public:
        float v[4];

        struct {
            public:
            float x;
            float y;
            float z;
            float w;
        };
    };
};

#endif