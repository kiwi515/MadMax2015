#ifndef ENGINE_MATRIX4F_H
#define ENGINE_MATRIX4F_H


class CMatrix4f {
public:
    union {
        struct {
            public:
            float e[16];
            float m[4][4];
        };
        public:
        float m00;
        float m01;
        float m02;
        float m03;
        float m10;
        float m11;
        float m12;
        float m13;
        float m20;
        float m21;
        float m22;
        float m23;
        float m30;
        float m31;
        float m32;
        float m33;
    };

      public: 
      CMatrix4f(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
};

#endif