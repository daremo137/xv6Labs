#define PAGECNT(paaddr) ((uint64)(paaddr - KERNBASE) / PGSIZE)
#define MAXPAGECNT PAGECNT(PHYSTOP)
#define PAGE_REFCNT(paaddr) page_cnt[PAGECNT(paaddr)]

int page_cnt[MAXPAGECNT];
