#ifndef _MPOOL_H_
#define	_MPOOL_H_

#ifdef	__cplusplus
extern "C" {
#endif

/* Forward declaration */
struct mpool;


struct mpool *mpool_create (size_t size);
void mpool_free (struct mpool *pool);

void *mpool_malloc (struct mpool *pool, size_t size);
void *mpool_strdup (struct mpool *pool, const char *str);
void *mpool_strndup (struct mpool *pool, const char *str, size_t n);


#ifdef	__cplusplus
}
#endif

#endif	/* _MPOOL_H_ */
