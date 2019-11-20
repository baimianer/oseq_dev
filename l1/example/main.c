/***********************************************************
  *File Name: 
  *Description: 
  *Author: Chen Xi
  *Email: chenxi1@genomics.cn
  *Create Time: 2018-11-09 17:01:24
  *Edit History: 
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sam.h>
#include <hts.h>

int
main (int argc, char * argv[])
{
  if (argc < 2) {
    fprintf (stderr, "./sam_read_example <bam>\n");
    return 1;
  }

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

  while (sam_read1(in, head, b) >= 0) {
    // read name
    printf ("%s\t", b->data);

    // read flag
    printf ("%d\t", c->flag);

    // chr and pos
    printf ("%s\t%d\t", head->target_name[c->tid], c->pos);

    // mapping quality
    printf ("%d\t", c->qual);

    // mate chr and pos
    printf ("%s\t%d\t", head->target_name[c->mtid], c->mpos);

    // insert size
    printf ("%d\n", c->isize);
  }

  bam_destroy1 (b);
  sam_close (in);
  bam_hdr_destroy (head);

  return 0;
}
