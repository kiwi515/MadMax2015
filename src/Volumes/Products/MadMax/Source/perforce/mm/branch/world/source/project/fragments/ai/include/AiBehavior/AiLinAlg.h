#ifndef PROJECT_FRAGMENTS_AI_LIN_ALG_H
#define PROJECT_FRAGMENTS_AI_LIN_ALG_H

struct SVector4f {
    public: 
    float x;
    float y;
    float z;
    float w;
};

struct SMatrix4f {
  union {
    public: 
    float e[16];
    struct {
      public: 
        SVector4f x;
        SVector4f y;
        SVector4f z;
        SVector4f w;
    };
  };
};

#endif