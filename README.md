
Unix, C, and C++
Function Reference
Time


Index:
   CPU time usage:
      clock_t        Explanation of type for CPU times.
      clock          Get CPU time consumed
      getrusage      Get CPU time consumed
   Time of Day and Date:
      time_t         Explanation of type for simple times.
      time           Get actual time, resolution 1 second.
      ctime          Convert time (seconds) to printable string.
      tm             Explanation of tm type for d,m,y,h,m,s.
      localtime      Split time (seconds) into d,m,y,h,m,s.
      gmtime         Split time (seconds) into d,m,y,h,m,s GMT.
      gettimeofday   Get actual time, resolution 0.01 seconds.
      mktime         Converts d,m,y,h,m,s parts into seconds.
      timegm         Converts d,m,y,h,m,s parts into seconds GMT.



  The type time_t
      include: <time.h>
       Is exactly identical to "int" in behaviour. You may assign int values
       to a time_t variable, and vice-versa, and print time_t values using
       the %d format, and everything.
       In the future, either time_t will cease to be identical to int, or
       the meaning of "int" will change from 4-byte-integer to 8-byte-integer,
       otherwise unix will have its own "Y2K" problem at 10:14:08pm on
       Monday 18th January 2038, which will appear to be 3:45:52pm on Friday
       13th December 1901.
         time_t values are produced from the clock by time.
         time_t values are produced from y,m,d,h,m,s parts by mktime and timegm.
         time_t values are analysed into y,m,d,h,m,s by localtime and gmtime.
         time_t values are converted to readable strings by ctime.




  time_t time(void)
  time_t time(time_t *ptr)
      include: <time.h>
      Returns the number of seconds that have passed since midnight, 1st
      January 1970 GMT (or 7pm, 31st December 1969 EST). If the parameter
      is not NULL, the same value is stored in the location pointed to.
      Follow this link for information on the time_t type.
      The value returned may be used as a reliable measure of elapsed time,
      and may be passed to ctime() for conversion into a human-readable 
      string.
         Example:
             time_t t1=time(NULL);
             do_something_long();
             time_t t2=time(NULL);
             printf("%d seconds elapsed\n", t2-t1);
      time_t values are produced from the clock by time.
      time_t values are produced from y,m,d,h,m,s parts by mktime and timegm.
      time_t values are analysed into y,m,d,h,m,s by localtime and gmtime.
      time_t values are converted to readable strings by ctime.




  char *ctime(time_t *ptr)
  char *ctime_r(time_t *ptr, char *output)
      include: <time.h>
      Note that the parameter must be a pointer to the numeric time.
      time_t values are produced by time.
      Converts the time provided into a human-readable string, the format
      is illustrated by these examples:
                         Mon Jan 18 22:14:07 2038\n
                         Fri Jan  8 12:14:07 2038\n
                         Mon Jan 18 08:20:37 2038\n
                         Fri Dec 13 15:45:52 1901\n
      Dates are padded with a space if only one digit long, and time components
      are given leading zeros. The date is always absurdly followed by a 
      newline character, which usually has to be removed.
      Warning the char* string returned is a static array, every call
      of ctime uses the same array, so the results of any call are always 
      overwritten by the bext call.
      Ctime_r is exactly the same as ctime, except that the caller must provide
      an array of chars big enough to hold the result. The return value is the
      same as the second parameter.
         Example:
             time_t tim=time(NULL);
             char *s=ctime(&tim);
             s[strlen(s)-1]=0;        // remove \n
             printf("it is %s now.\n", s);
      time_t values are produced from the clock by time.
      time_t values are produced from y,m,d,h,m,s parts by mktime and timegm.



  int gettimeofday(timeval *tp, NULL)
      include: <sys/time.h>
      Note In C programs (as opposed to C++) the word "struct" must
      appear before "timeval".
      Gets the time of day. The parameter must be a pointer to a previously
      declared timeval variable (or in C, a struct timeval variable). This
      struct type is also defined in <sys/time.h>. A timeval has two
      components, both ints. One (called tv_sec) is exactly the value that
      would be returned by time, the time in seconds since 1/1/1970.
      The other (called tv_usec) is the number of microseconds into that
      second. Don't be fooled: although the units are microseconds, the value
      is nothing like that accurate. On many systems, 10000 is added 100
      times per second.
         Example:
             timeval tim;
             gettimeofday(&tim, NULL);
             double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
             do_something_long();
             gettimeofday(&tim, NULL);
             double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
             printf("%.6lf seconds elapsed\n", t2-t1);
      The second parameter (NULL) used to be to retrieve the local time zone,
      but time zones are no-longer handled that way.




  The type clock_t
      include: <time.h>
       Is exactly identical to "unsigned int" in behaviour. You may assign 
       int values to a time_t variable, and vice-versa, and print time_t 
       values using the %u format, and everything.




  clock_t clock(void)
      include: <time.h>
      Returns the amount of processor time actually used by the current
      process, measured in units of CLOCKS_PER_SEC, which on this system
      is 128.
         Example:
             clock_t t1=clock();
             do_something_long();
             clock_t t2=clock();
             printf("%.4lf seconds of processing\n", (t2-t1)/(double)CLOCKS_PER_SEC);
      The clock function provides a very simple interface, but
      does not distinguish between time spent on user code and time spent 
      executing system functions; it merely measures the total CPU time
      devoted so far to the current process. For more detailed and more
      accurate information see getrusage.
      Note: this function is available under DOS and Windows, but the more
      accurate version, getrusage is unix only.




  int getrusage(int target, rusage * results)
      include: <sys/time.h>
      include: <sys/resource.h>
      Not avalibale under DOS or Windows.
      Returns 0 for success, and negative for failure; there are no reasonable
      reasons for failure to occur.
      The target parameter must be one of the two pre-defined values
      RUSAGE_SELF or RUSAGE_CHILDREN. RUSAGE_SELF measures only the current
      process, RUSAGE_CHILDREN measures only subprocesses that have already
      terminated. Unix provides no useful way to obtain information for
      still-running subprocesses.
      The results parameter is a pointer to a struct that the calling
      program must create, and which will be filled in with statistics on
      resource information. The fields of this struct are as follows:
         (the first two fields are structs of type timeval, see below)
             ru_utime       time spent executing user code
             ru_stime       time spent executing system functions
         (the remaining fields are ints)
             ru_maxrss      max resident set size (physical memory allocated)
             ru_ixrss       memory size for code
             ru_idrss       memory size for statics, globals, and new/malloc
             ru_isrss       stack size (memory used by local variables)
             ru_minflt      minor page faults: "page reclaims"
             ru_majflt      major page faults: swaps in
             ru_nswap       page swaps
             ru_inblock     block input operations, disc etc
             ru_oublock     block output operations, disc, etc
             ru_msgsnd      messages sent
             ru_msgrcv      messages received
             ru_nsignals    signals received
             ru_nvcsw       voluntary context switches (process loses CPU)
             ru_nivcsw      involuntary context switches (process loses CPU)
      The timeval struct used to measure time has only two fields, and
      both are unsigned ints. They are named tv_sec and tv_usec, and
      jointly represent one single value. tv_sec*1000000+tv_usec gives the
      number of microseconds.
         Example:
             double getcputime(void)        
             { struct timeval tim;        
               struct rusage ru;        
               getrusage(RUSAGE_SELF, &ru);        
               tim=ru.ru_utime;        
               double t=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;        
               tim=ru.ru_stime;        
               t+=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;        
               return t; }        
      This example function returns the total CPU time consumed by the current
      process, measured in seconds, as a double precision floating point number.
      It adds together the user time and the system time.
      Note: Although the format used is capable of measuring time to an accuracy
      of a microsecond, do not expect that much precision from any real system.




  The type tm
        or struct tm in C.
      include: <time.h>
       Is used to represent a time in a structured form, with different components
       for second, minute, hour, day, month, year, and day-of-week. Its definition
       is as follows:
           struct tm
           { int tm_sec;      // 0 to 59 (or 60 for occasional rare leap-seconds)
             int tm_min;      // 0 to 59
             int tm_hour;     // 0 to 23
             int tm_mday;     // 1 to 31
             int tm_mon;      // 0 to 11, stupidly 0=January, 11=December
             int tm_year;     // year-1900, so 79 means 1979, 103 means 2003
             int tm_wday;     // 0 to 6, 0=Sunday, 1=Monday, ..., 6=Saturday
             int tm_yday;     // 0 to 365, 0=1st January
             int tm_isdst;    // 0 to 1, 1=DST is in effect, 0=it isn't
             char *tm_zone;   // time zone, e.g. "PDT", "EST".
             int tm_gmtoff; } // time zone in seconds from GMT; EST=-18000, WET=3600
       tm structures are produced from by localtime and gmtime.
       tm structures are converted to strings by asctime.
       tm structures are converted to seconds by mktime and .





  tm * localtime(time_t * tim)
  tm * gmtime(time_t * tim)
  tm * localtime_r(time_t * tim, tm * output)
  tm * gmtime_r(time_t * tim, tm * output)
  struct tm * localtime(time_t * tim) in C
  struct tm * gmtime(time_t * tim) in C
  struct tm * localtime_r(time_t * tim, struct tm * output) in C
  struct tm * gmtime_r(time_t * tim, struct tm * output) in C
      include: <time.h>
      The parameter is a pointer to a time_t (effectively an int) variable containing
      the time in seconds since 1/1/1970. The represented time is analysed to produce
      all the components: hour, minute, second, day, month, year, day-of-week, time zone.
      Those values are stored in a tm structure, and a pointer to that structure is
      returned. All calls to localtime and gmtime use the same static structure, so
      each call overwrites the results of the previous call.
      Localtime uses the local time zone, gmtime converts to GMT (or UTC).
      Localtime_r and gmtime_r are exactly the same as localtime and gmtime, except
      that the caller must provide a pointer to an existing tm object, and the components
      of that object will be filled in; the return result is the same as the second parameter.
         time_t values are produced from the clock by time.
         tm structures are converted to strings by asctime.
      Example:
             time_t tim=time(NULL);
             tm *now=localtime(&tim);
             printf("Date is %d/%02d/%02d\n", now->tm_year+1900, now->tm_mon+1, now->tm_mday);
             printf("Time is %02d:%02d\n", now->tm_hour, now->tm_min);





  char * asctime(tm * input)
  char * asctime_r(tm * input, char * output)
  char * asctime(struct tm * input) in C.
  char * asctime_r(struct tm * input, char * output) in C.
      include: <time.h>
       A tm object must already be created and completely filled with appropriate
       values representing sec, min, hour, mday, mon, and year. It is not necessary
       to provide values for mday and wday. (see here for tm details).
       Out of range values are accepted (e.g. hour=-1 becomes hour 23 of previous day).
       The string returned is actually created by ctime; see ctime's
       explanation for details of the format.
       Asctime_r is exactly the same as asctime, except that the caller must provide
       an array of chars beg enough to contain the result. The returned value is always
       the same as the second parameter.






  time_t mktime(tm * tim)
  time_t timegm(tm * tim)
  time_t mktime(struct tm * tim) in C
  time_t timegm(struct tm * tim) in C
      include: <time.h>
       The time and date recorded in a tm structure are decoded and converted to
       the number of seconds since 1/1/1970.
       Using mktime immediately followed by localtime is a good way to normalise the
       values in a tm struct.
