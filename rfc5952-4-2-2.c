/*
 rfc5952-4-2-2.c

 Date Created: Sat Mar  2 19:06:58 2013
 Author:       Simon Leinen  <simon.leinen@switch.ch>

 Check whether inet_ntop() conforms to RFC 5952, in particular the
 MUST NOT clause in section 4.2.2.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

int
main ()
{
  const char *rfc5952ly_correct = "2001:db8:0:1:1:1:1:1";
  const char *rfc5952ly_incorrect = "2001:db8::1:1:1:1:1";

  char outbuf[100];
  struct sockaddr_in6 addr6;

  if (inet_pton (AF_INET6, rfc5952ly_correct, (char *) &addr6) == -1)
    {
      fprintf (stderr, "Bug in inet_pton() call\n");
      exit (1);
    }
  if (inet_ntop (AF_INET6, &addr6, outbuf, 100) == 0)
    {
      fprintf (stderr, "Bug in inet_ntop() call\n");
      exit (2);
    }
  if (strcasecmp (rfc5952ly_correct, outbuf) == 0)
    {
      printf ("Congratulations, your inet_ntop() conforms to RFC 5952 4.2.2\n");
    }
  else if (strcasecmp (rfc5952ly_incorrect, outbuf) == 0)
    {
      printf ("ATTENTION: Your system's inet_ntop() violates RFC 5952 4.2.2!\n");
    }
  else
    {
      printf ("ATTENTION: Your system's inet_ntop() may violate RFC 5952.\n");
      printf ("Interestingly, rather than the expected\n \"%s\" (correct) or\n",
	      rfc5952ly_correct);
      printf (" \"%s\" (incorrect), your system generates:\n \"%s\".\n",
	      rfc5952ly_incorrect, outbuf);
    }
  return 0;
}
