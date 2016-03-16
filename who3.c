/* who3.c - who with buffered reads
 *        - supresses empty records
 *        - formats time nicely
 *        - buffers input (using utmplib)
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>


#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

#define SHOWHOST


static char utmpbuf[NRECS * UTSIZE];  /* storage    */
static int num_recs;                  /* num stored */
static int cur_rec;                   /* next to go */
static int fd_utmp = -1;              /* read from  */


utmp_open(char * filename)
{
	fd_utmp = open(filename, O_RDONLY); /* open it       */
	cur_rec = num_recs = 0;             /* no recs yet   */
	return fd_utmp;
}

struct utmp *utmp_next()
{
	struct utmp *recp;
	if(fd_utmp == -1)
		return NULLUT;
	if(cur_rec==num_recs && utmp_reload()==0) 
		return NULLUT;
				/* get address of next record */
	recp = (struct utmp *) &utmpbuf[cur_rec * UTSIZE];
	cur_rec++;
	return recp;
}

int utmp_reload()
/*
 * read next bunch of records into buffer
*/
{
	int amt_read;

	amt_read= read(fd_utmp, utmpbuf, NRECS * UTSIZE);

	num_recs=amt_read/UTSIZE;
	cur_rec=0;
	return num_recs;
}

utmp_close()
{
	if(fd_utmp != -1)
		close(fd_utmp);
}

void show_info(struct utmp *);
void showtime(time_t);


int main()
{
	struct utmp *utbufp,      /* holds pointer to next rec */
		    *utmp_next(); /* returns pointer to next   */
		if ( utmp_open( UTMP_FILE) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	while ( ( utbufp = utmp_next () ) != ((struct utmp *)  NULL) )
		show_info(utbufp);
	utmp_close();
	return 0;
}

void show_info (struct utmp *utbufp)
{
	if (utbufp -> ut_type != USER_PROCESS)
		return;
		printf("%-8.8s", utbufp->ut_name);
	printf(" ");
	printf("%-8.8s", utbufp->ut_line);
	printf(" ");
	showtime(utbufp->ut_time);

	#ifdef SHOWHOST
		if(utbufp->ut_host[0] != '\0')
		printf(" (%s)", utbufp->ut_host);
	#endif
		printf("\n");
}

void showtime( long timeval)
{
	char *cp;
	cp = ctime(&timeval);

	printf("%12.12s", cp+4);
} 
