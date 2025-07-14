/* dbg_mem.h — instrumentation malloc/free (activer pour traquer les leaks) */
#ifndef DBG_MEM_H
# define DBG_MEM_H

# include <stdio.h>
# include <stdlib.h>

static inline void *dbg_malloc(size_t s, const char *f, int l)
{
    void *p = malloc(s);
    fprintf(stderr, "[M] %p %zu (%s:%d)\n", p, s, f, l);
    return p;
}
static inline void dbg_free(void *p, const char *f, int l)
{
    fprintf(stderr, "[F] %p (%s:%d)\n", p, f, l);
    free(p);
}

/* Redéfinit malloc/free **APRÈS** toutes les includes système */
# define malloc(x)  dbg_malloc((x), __FILE__, __LINE__)
# define free(x)    dbg_free((x), __FILE__, __LINE__)

#endif /* DBG_MEM_H */
