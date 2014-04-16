#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using std::vector;

int main(int argc, char **argv)
{
  //check command line arguments
  if (argc < 2) {
    fprintf(stderr, "Error, program usage: %s [inputfilename]\n", argv[0]);
    exit(1);
  }

  //loop over all the command line inputs
  for (int argnum=1; argnum < argc; argnum++) {
    //open the input file
    FILE* fp;  //pointer to file we will read in
    if ((fp = fopen(argv[argnum], "r"))==NULL) {
      fprintf(stderr, "Error, unable to open input file %s\n", argv[1]);
      continue; //gracefully skip over this bad filename
    }
    
    int a;  //storage for the current data characer
    vector<int> byte_counters(256, 0);
    int total_bytes = 0;
    //now calculate the p(x) probabilities of each possible byte (0-255)
    while ((a = fgetc(fp))!=EOF) {  
      byte_counters[a]++;
      total_bytes++;
    }
    fclose(fp); //finished with the input file
    
    //now calculate the entropy value
    double h = 0.0;  //entropy
		for (const int& byte_counter : byte_counters) {
      double p_i  = (double)byte_counter / total_bytes;
      if (p_i > 0.0) {
				//avoid the inf value returned by log(0.0)
				h -= p_i * (log(p_i) / log(2));
			}
    }
    printf("%s:\t%g\n", argv[argnum], h);  //output our entropy value for the file
  }

  return 0;
}
