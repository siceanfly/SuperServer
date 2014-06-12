/***************************************************************************
 *            main.c
 *
 *  Copyright 2005 Dimitur Kirov
 *  dkirov@gmail.com
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "fileutils.h"
#include <pthread.h>


void *HttpStart(void *ptr);
void *FtpStart(void *ptr)
{
   struct arg *s=ptr;
   int argc = s->ac;
   char **argv = s->av;
   struct cmd_opts *copts= malloc(sizeof(struct cmd_opts));
	int result = pars_cmd_args(copts,argc,argv);
	switch(result) {
		case 0:
			return create_socket(copts);
		case -1:
			break;
		default:
			return 1;
	}

}

int main(int argc,char *argv[])
{
   struct arg *p;
   p = (struct arg*)malloc(sizeof(struct arg));
   p->ac = argc;
   p->av = argv;
   pthread_t httpThread,ftpThread;
   int retH = pthread_create(&httpThread,NULL,HttpStart,p);
   int retF = pthread_create(&ftpThread,NULL,FtpStart,p);
   if(retH)
   {
      printf("Create Http pthread error!\n");
      return retH;
   }
   if(retF)
   {
      printf("Create Ftp thread error!\n");
      return retF;
   }

   pthread_join(httpThread,NULL);
   pthread_join(ftpThread,NULL);
   free(p);

	return 0;
}
