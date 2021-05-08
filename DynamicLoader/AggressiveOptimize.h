#ifdef NDEBUG
//#pragma optimize("NOWIN98",on)

//#pragma comment(linker,"/merge:.xdata=.rdata")
//#pragma comment(linker,"/merge:.pdata=.rdata")
//#pragma comment(linker,"/merge:.rdata=.text")


//#pragma comment(linker,"/merge:.xdata=.rdata")
//#pragma comment(linker,"/merge:.pdata=.rdata")
//#pragma comment(linker,"/merge:.data=.rdata")
//#pragma comment(linker,"/merge:.reloc=.rdata")
//#pragma comment(linker,"/merge:.text=.rdata")

//#pragma comment(linker,"/nostub")
//#pragma comment(linker,"/ALIGN:128")

//#pragma comment(linker,"/STUB:filename")
#endif // NDEBUG
