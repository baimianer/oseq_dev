/***********************************************************
  *File Name: 
  *Description: 
  *Author: Xue Siming
  *Email: xuesimnig@genomics.cn
  *Create Time: 2019-11-21 17:01:24
  *Edit History: 
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sam.h>
#include <hts.h>
#define ISIZE_BATCH 1000000 //1,000,000

static int
cmp(const void * a, const void * b)
{
	int isize_a = *(int *) a;
	int isize_b = *(int *) b;

	if(isize_a == isize_b)
		return 0;
	else if(isize_a > isize_b)
		return 1;
	else
	  	return -1;
											}

int
main (int argc, char * argv[])
{
  if (argc < 2) {
    fprintf (stderr, "./sam_read_example <bam>\n");
    return 1;
  }
  double mean;
  double std;
  uint8_t * s;
  uint8_t * q;
  int i;
  uint32_t opr;
  uint32_t len;
  uint32_t * cigar;
  bam1_t * b;
  bam1_core_t * c;
  samFile * in;
  bam_hdr_t * head;
  
  b = bam_init1 ();
  c = &b->core;

  if ((in = sam_open(argv[1],"rb")) == NULL) {
    fprintf (stderr, "fail to open bam file: %s\n", argv[1]);
    abort ();
  }

  if ((head = sam_hdr_read(in)) == NULL) {
    fprintf (stderr, "fail to read header info from: %s\n", argv[1]);
    abort ();
  }
  int * isize_array;
  long long isize_c, isize_m;
  isize_m = ISIZE_BATCH;
  isize_array = (int *)malloc(sizeof(int)*isize_m);

  while (sam_read1(in, head, b) >= 0) {
    // read name
    //printf ("%s\t", b->data);

    // read flag
    //printf ("%d\t", c->flag);

    // chr and pos
    //printf ("%s\t%d\t", head->target_name[c->tid], c->pos);

    // mapping quality
    //printf ("%d\t", c->qual);

    // mate chr and pos
    //printf ("%s\t%d\t", head->target_name[c->mtid], c->mpos);
    //printf("mapq\t%d\n",c->qual);  
    if (c->qual <30){
        continue;
    }
    isize_array[isize_c++]=abs(c->isize);
    // insert size
    
    //printf ("%d\n", c->isize);
  }

  bam_destroy1 (b);
  sam_close (in);
  bam_hdr_destroy (head);
  //Calculate mean and standard deviation
 qsort(isize_array, isize_c, sizeof(int), cmp);
 int one_quarter_idx = isize_c / 4;
 int three_quarter_idx = isize_c * 3 / 4;
 int median_idx = isize_c / 2;
 int lowest_cut_idx = isize_c / 100;
 int highest_cut_idx = isize_c * 99 / 100;
 int one_quarter;
 int three_quarter;
 int median;
 int lowest_cut;
 int highest_cut;
 one_quarter= isize_array[one_quarter_idx-1];
 three_quarter = isize_array[three_quarter_idx-1];
 median = isize_array[median_idx-1];
 lowest_cut = isize_array[lowest_cut_idx-1];
 highest_cut = isize_array[highest_cut_idx-1];
 printf("read_num:%d\tone_quarter:%d\tthree_quarter:%d\tmedian:%d\tlowest_cut:%d\thighest_cut:%d\n",isize_c,one_quarter,three_quarter,median,lowest_cut,highest_cut);

  return 0;
}
