#ifndef LIB_RESOURCE_CACHE_PTR_H
#define LIB_RESOURCE_CACHE_PTR_H

template <typename... Args>
class TResourceCachePtr {
    private:
    SResourceHandle* m_Handle;
};

#endif