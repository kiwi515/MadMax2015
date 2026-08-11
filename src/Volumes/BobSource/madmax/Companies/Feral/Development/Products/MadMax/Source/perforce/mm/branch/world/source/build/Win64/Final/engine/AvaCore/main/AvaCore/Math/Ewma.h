#ifndef ENGINE_EWMA_H
#define ENGINE_EWMA_H

class CEWMA {
    private:
    float m_Average;
    float m_Alpha;
    bool m_First;

    private:
    static const float m_EWMAEpsillon;
};

#endif