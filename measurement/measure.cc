#include <stdint.h>
#include <iostream>

//this tool is compatible for x86_64 architecture only
#ifdef _WIN32                //  Windows
   #include <intrin.h>

   uint64_t rdtsc()
   {
       return __rdtsc();
   }
#else                        //  Linux/GCC
   uint64_t rdtsc()
   {
      unsigned int lo,hi;
      __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
      return ((uint64_t)hi << 32) | lo;
   }
#endif //_WIN32 

#define EXPR_TIME_CONS_AVER(nCount, expr, bShowCurTime)\
{\
   char ExprText[sizeof(#expr) + 1] = {0};\
   memcpy(ExprText, #expr, sizeof(#expr));\
   if(bShowCurTime == true)\
     std::cout<<"=== "<<ExprText<<" === start"<<std::endl;\
   uint64_t ui1, ui2, uiTicks, uiAverage = 0;\
   for(int iIn = 0; iIn < nCount; ++iIn)\
   {\
      ui1 = rdtsc();\
      expr;\
      ui2 = rdtsc();\
      uiTicks = ui2 - ui1;\
      uiAverage += uiTicks;\
      if(bShowCurTime == true)\
         std::cout<<uiTicks<<std::endl;\
   }\
	std::cout<<"=== "<<ExprText<<" average == "<<uiAverage / nCount<<"\n\n";\
}



// for testing

int main(int argc,char ** argv)
{
	return 0;
}
