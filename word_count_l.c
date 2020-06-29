/*
 * Implementation of the word_count interface using Pintos lists.
 *
 * You may modify this file, and are expected to modify it.
 */

/*
 * Copyright © 2019 University of California, Berkeley
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PINTOS_LIST
#error "PINTOS_LIST must be #define'd when compiling word_count_l.c"
#endif

#include "word_count.h"

void init_words(word_count_list_t *wclist) {
	list_init(wclist);	
}

size_t len_words(word_count_list_t *wclist) {
  size_t len = 0;
  for(struct list_elem *w = list_begin(wclist); w != list_end(wclist); w = list_next(w)) {
		  len++;
  }
  return len;
}

word_count_t *find_word(word_count_list_t *wclist, char *word) {
  struct list_elem *w = list_begin(wclist);
  struct word_count *wc = list_entry(w, struct word_count, elem);

  while ((w != list_end(wclist)) && (strcmp(word, wc->word) != 0)) {
		  w = list_next(w);
		  wc = list_entry(w, struct word_count, elem);
  }
  return wc;
}

word_count_t *add_word(word_count_list_t *wclist, char *word) {
  word_count_t *wc = find_word(wclist, word);

  if (wc->word) {
  	wc->count++;
  } else if ((wc = malloc(sizeof(word_count_t))) != NULL) {
	  wc->word = word;
	  wc->count = 1;
          list_push_front(wclist, &wc->elem);
  } else {
	  perror("malloc");
  }
  return wc;
}

void fprint_words(word_count_list_t *wclist, FILE *outfile) {
  for (struct list_elem *w = list_begin(wclist); w != list_end(wclist); w = list_next(w)) {
	  word_count_t *wc = list_entry(w, word_count_t, elem);
	  fprintf(outfile, "%8d\t%s\n", wc->count, wc->word);
  }
}

static bool less_list(const struct list_elem *ewc1,
                      const struct list_elem *ewc2, void *aux) {
   // return *aux(listr_entry(ewc1,word_count_t,elem),list_entry(ewc2,wourd_count_t,elem))
   bool (*less) (word_count_t *w1, word_count_t *w2);
   word_count_t *w1 = list_entry(ewc1,word_count_t,elem);
   word_count_t *w2 = list_entry(ewc2,word_count_t,elem);
   less = aux; 
   return less(w1, w2);
}

void wordcount_sort(word_count_list_t *wclist,
                    bool less(const word_count_t *, const word_count_t *)) {
  list_sort(wclist, less_list, less);
}
