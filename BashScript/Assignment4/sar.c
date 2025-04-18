<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>sar.c</title>
<style type="text/css">
.enscript-comment { font-style: italic; color: rgb(178,34,34); }
.enscript-function-name { font-weight: bold; color: rgb(0,0,255); }
.enscript-variable-name { font-weight: bold; color: rgb(184,134,11); }
.enscript-keyword { font-weight: bold; color: rgb(160,32,240); }
.enscript-reference { font-weight: bold; color: rgb(95,158,160); }
.enscript-string { font-weight: bold; color: rgb(188,143,143); }
.enscript-builtin { font-weight: bold; color: rgb(218,112,214); }
.enscript-type { font-weight: bold; color: rgb(34,139,34); }
.enscript-highlight { text-decoration: underline; color: 0; }
</style>
</head>
<body id="top">
<h1 style="margin:8px;" id="f1">sar.c&nbsp;&nbsp;&nbsp;<span style="font-weight: normal; font-size: 0.5em;">[<a href="sar.c">plain text</a>]</span></h1>
<hr/>
<div></div>
<pre>
<span class="enscript-comment">/*
 * Portions Copyright (c) 1999-2003 Apple Computer, Inc. All Rights
 *  Reserved.
 *
 *  This file contains Original Code and/or Modifications of Original Code
 *  as defined in and that are subject to the Apple Public Source License
 *  Version 2.0 (the 'License'). You may not use this file except in
 *  compliance with the License. Please obtain a copy of the License at
 *  <a href="http://www.opensource.apple.com/apsl/">http://www.opensource.apple.com/apsl/</a> and read it before using this
 *  file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
*/</span>

<span class="enscript-comment">/*
  cc -Wall -I. -I ../sadc.tproj -O -o  sar sar.c
*/</span>

#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;stdio.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;stdlib.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;unistd.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;ctype.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;time.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;fcntl.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;errno.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;signal.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;mach/mach.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/param.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/sysctl.h&gt;</span>

#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;sadc.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;sar.h&gt;</span>


#<span class="enscript-reference">define</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span> 1

<span class="enscript-comment">/* Options used only for launching sadc */</span>
<span class="enscript-type">int</span> t_interval = 5; 	        <span class="enscript-comment">/* in seconds              */</span>
<span class="enscript-type">char</span> * t_intervalp = <span class="enscript-string">&quot;5&quot;</span>;
<span class="enscript-type">int</span> n_samples  = 1;	        <span class="enscript-comment">/* number of sample loops  */</span>
<span class="enscript-type">char</span> * n_samplesp = <span class="enscript-string">&quot;1&quot;</span>;

<span class="enscript-comment">/* Used only for storing the binary output after launching sadc */</span>
<span class="enscript-type">char</span> *outfile  = NULL;          <span class="enscript-comment">/* output file             */</span>
<span class="enscript-type">int</span> ofd        = 0;		<span class="enscript-comment">/* output file descriptor  */</span>

<span class="enscript-comment">/*
 * When launching sadc, this file descriptor reads sadc's stdout
 *    via pipe.
 * When not launching sadc, this file descriptor will be either
 *    the input file passed in with the -f flag
 *    or the standard input file /var/log/sa/saXX
 */</span>
<span class="enscript-type">int</span> ifd        = 0;		<span class="enscript-comment">/* input file descriptor   */</span>   
<span class="enscript-type">char</span> *infile   = NULL;          <span class="enscript-comment">/* input file              */</span>



<span class="enscript-comment">/* Used when we have to luanch sadc */</span>
pid_t pid;
<span class="enscript-type">int</span> fd[2];  <span class="enscript-comment">/* read from fd[0], write to fd[1] */</span>

<span class="enscript-type">char</span> *optionstring1 =  <span class="enscript-string">&quot;Adgn:puo:&quot;</span>;
<span class="enscript-type">char</span> *optionstring1_usage = <span class="enscript-string">&quot;/usr/bin/sar [-Adgpu] [-n { DEV | EDEV | PPP } ] [-o filename] t [n]&quot;</span>;
<span class="enscript-type">char</span> *optionstring2 = <span class="enscript-string">&quot;Adgn:pue:f:i:s:&quot;</span>;
<span class="enscript-type">char</span> *optionstring2_usage = <span class="enscript-string">&quot;/usr/bin/sar [-Adgpu] [-n { DEV | EDEV | PPP }] [-e time] [-f filename] [-i sec] [-s time]&quot;</span>;


<span class="enscript-comment">/* option flags */</span>
<span class="enscript-type">int</span> aflag = 0;
<span class="enscript-type">int</span> Aflag = 0;
<span class="enscript-type">int</span> bflag = 0;
<span class="enscript-type">int</span> cflag = 0;
<span class="enscript-type">int</span> dflag = 0;  <span class="enscript-comment">/* drive statistics */</span>
<span class="enscript-type">int</span> gflag = 0;  <span class="enscript-comment">/* page-out activity */</span>
<span class="enscript-type">int</span> kflag = 0;
<span class="enscript-type">int</span> mflag = 0;

<span class="enscript-type">int</span> nflag = 0;  <span class="enscript-comment">/* network statistics */</span>
<span class="enscript-type">int</span> network_mode = 0;
<span class="enscript-type">char</span> *sadc_mflagp = <span class="enscript-string">&quot;-m&quot;</span>;
<span class="enscript-type">char</span> *sadc_ppp_modep = <span class="enscript-string">&quot;PPP&quot;</span>;

<span class="enscript-type">int</span> pflag = 0;  <span class="enscript-comment">/* page-in activity */</span>
<span class="enscript-type">int</span> qflag = 0;
<span class="enscript-type">int</span> rflag = 0;
<span class="enscript-type">int</span> uflag = 0;   <span class="enscript-comment">/* cpu utilization - this is the only default */</span>
<span class="enscript-type">int</span> vflag = 0;
<span class="enscript-type">int</span> wflag = 0;
<span class="enscript-type">int</span> yflag = 0;
<span class="enscript-type">int</span> set_default_flag = 1;
<span class="enscript-type">int</span> flag_count = 0;

<span class="enscript-comment">/*
 *  To get the current time of day in seconds
 *  based on a 24 hour clock, pass in the time_t from time()
 *  the remainder is the current time in seconds
*/</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">HOURS_PER_DAY</span> 24
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">MINS_PER_HOUR</span> 60
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">SECS_PER_MIN</span> 60
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">SECS_PER_DAY</span> (SECS_PER_MIN * MINS_PER_HOUR * HOURS_PER_DAY)

<span class="enscript-comment">/* end time delimiter -- converted from hh:mm:ss to seconds */</span>
time_t end_time = 0;

<span class="enscript-type">int</span> iflag = 0;
<span class="enscript-type">int</span> iseconds = 0;  <span class="enscript-comment">/* interval seconds, default = 0 implies all samples are
		    * printed */</span>

<span class="enscript-comment">/* start time delimiter -- converted from hh:mm:ss to seconds */</span>
time_t start_time = 0;

<span class="enscript-type">int</span> oflag = 0;
<span class="enscript-type">int</span> fflag = 0;

<span class="enscript-comment">/* stat records average and previous */</span>
<span class="enscript-type">struct</span> vm_statistics       prev_vmstat,  avg_vmstat, cur_vmstat;
host_cpu_load_info_data_t  prev_cpuload, avg_cpuload, cur_cpuload;
<span class="enscript-type">struct</span> drivestats_report   *dr_head = NULL;

<span class="enscript-comment">/* internal table of drive path mappings */</span>
<span class="enscript-type">struct</span> drivepath *dp_table = NULL;
<span class="enscript-type">int</span> dp_count = 0;

<span class="enscript-comment">/* internal table of network interface statistics */</span>
<span class="enscript-type">struct</span> netstats_report *nr_table = NULL;
<span class="enscript-type">int</span> nr_count;
<span class="enscript-type">struct</span> netstats *netstat_readbuf = NULL;
size_t netstat_readbuf_size = 0;

<span class="enscript-type">int</span> avg_counter = 0;
<span class="enscript-type">int</span> avg_interval = 0;

<span class="enscript-type">extern</span> <span class="enscript-type">int</span> errno;

<span class="enscript-comment">/* Forward function declarations */</span>
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">exit_usage</span>();
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">open_output_file</span>(<span class="enscript-type">char</span> *path);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">open_input_file</span>(<span class="enscript-type">char</span> *path);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">read_record_hdr</span>(<span class="enscript-type">struct</span> record_hdr *hdr, <span class="enscript-type">int</span> writeflag);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">read_record_data</span>(<span class="enscript-type">char</span> *buf, size_t size, <span class="enscript-type">int</span> writeflag);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">write_record_hdr</span>(<span class="enscript-type">struct</span> record_hdr *hdr);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">write_record_data</span>(<span class="enscript-type">char</span> *buf, size_t size);
<span class="enscript-type">static</span> time_t <span class="enscript-function-name">convert_hms</span>(<span class="enscript-type">char</span> *string);
<span class="enscript-type">static</span> <span class="enscript-type">char</span> *<span class="enscript-function-name">get_hms_string</span>(time_t, <span class="enscript-type">char</span> *);
<span class="enscript-type">static</span> <span class="enscript-type">int</span> <span class="enscript-function-name">find_restart_header</span>(<span class="enscript-type">struct</span> record_hdr *);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">print_all_column_headings</span> (time_t timestamp);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">print_column_heading</span> (<span class="enscript-type">int</span> type, <span class="enscript-type">char</span> *timebufptr, <span class="enscript-type">int</span> mode);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">read_sample_set</span>(<span class="enscript-type">int</span>, time_t, <span class="enscript-type">struct</span> record_hdr *);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">do_main_workloop</span>();
<span class="enscript-type">static</span> <span class="enscript-type">int</span> <span class="enscript-function-name">bypass_sample_set</span>(<span class="enscript-type">struct</span> record_hdr *, time_t);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">skip_data</span>(<span class="enscript-type">int</span>);
<span class="enscript-type">static</span> <span class="enscript-type">int</span> <span class="enscript-function-name">get_cpu_sample</span>(<span class="enscript-type">int</span> flag, <span class="enscript-type">struct</span> record_hdr *hdr);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">print_cpu_sample</span>(<span class="enscript-type">char</span> *timebufptr);
<span class="enscript-type">static</span> <span class="enscript-type">int</span> <span class="enscript-function-name">get_vmstat_sample</span>(<span class="enscript-type">int</span> flag, <span class="enscript-type">struct</span> record_hdr *hdr);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">print_vmstat_sample</span>(<span class="enscript-type">char</span> *timebufptr);

<span class="enscript-type">static</span> <span class="enscript-type">int</span> <span class="enscript-function-name">get_drivestats_sample</span>(<span class="enscript-type">int</span> flag, <span class="enscript-type">struct</span> record_hdr *hdr);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">init_drivestats</span>(<span class="enscript-type">struct</span> drivestats_report *dr);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">print_drivestats_sample</span>(<span class="enscript-type">char</span> *timebufptr);
<span class="enscript-type">static</span> <span class="enscript-type">int</span> <span class="enscript-function-name">get_drivepath_sample</span>(<span class="enscript-type">int</span> flag, <span class="enscript-type">struct</span> record_hdr *hdr);

<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">set_cur_netstats</span>(<span class="enscript-type">struct</span> netstats_report *nr, <span class="enscript-type">struct</span> netstats *ns);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">init_prev_netstats</span>(<span class="enscript-type">struct</span> netstats_report *nr);
<span class="enscript-type">static</span> <span class="enscript-type">int</span> <span class="enscript-function-name">get_netstats_sample</span>(<span class="enscript-type">int</span> flag, <span class="enscript-type">struct</span> record_hdr *hdr);
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">print_netstats_sample</span>(<span class="enscript-type">char</span> *timebufptr);
    
<span class="enscript-type">static</span> <span class="enscript-type">void</span> <span class="enscript-function-name">exit_average</span>();

<span class="enscript-type">int</span>
<span class="enscript-function-name">main</span>(argc, argv)
    <span class="enscript-type">int</span> argc;
    <span class="enscript-type">char</span> *argv[];
{

    <span class="enscript-type">char</span>    ch;

    time_t curr_time;		<span class="enscript-comment">/* current time in seconds */</span>
    <span class="enscript-type">char</span> timebuf[26];
    <span class="enscript-type">char</span> filenamebuf[20];
    <span class="enscript-type">char</span> *optstring = NULL;
    <span class="enscript-type">int</span> optstringval;
    <span class="enscript-type">int</span> i;
    
    <span class="enscript-comment">/*
     * Detirmine which option string to use
     */</span>

    optreset=0;
    optstringval=0;
    
    <span class="enscript-keyword">while</span>((ch=getopt(argc, argv, <span class="enscript-string">&quot;aAbcdgkmn:pqruvwyo:e:f:i:s:&quot;</span>)) != EOF) {
	<span class="enscript-keyword">switch</span>(ch) {
	<span class="enscript-keyword">case</span> <span class="enscript-string">'o'</span>:
	    <span class="enscript-keyword">if</span> (optstringval == 2)
		exit_usage();
	    optstring=optionstring1;
	    optstringval=1;
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'e'</span>:
	<span class="enscript-keyword">case</span> <span class="enscript-string">'f'</span>:
	<span class="enscript-keyword">case</span> <span class="enscript-string">'i'</span>:
	<span class="enscript-keyword">case</span> <span class="enscript-string">'s'</span>:
	    <span class="enscript-keyword">if</span> (optstringval == 1)
		exit_usage();
	    optstring=optionstring2;
	    optstringval=2;
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-reference">default</span>:
	    <span class="enscript-comment">/* ignore for now */</span>
	    <span class="enscript-keyword">break</span>;
	}
    }

    <span class="enscript-keyword">if</span> (!optstring)
    {
	<span class="enscript-comment">/* still trying to determine which option string to use */</span>
	<span class="enscript-keyword">if</span> (argc - optind &gt; 0)
	{
	    optstring=optionstring1;  <span class="enscript-comment">/* we should have a t_second value */</span>
	    optstringval=1;
	}
	<span class="enscript-keyword">else</span>
	{
	    optstring=optionstring2;
	    optstringval=2;
	}
    }

    optreset = optind = 1;
    <span class="enscript-keyword">while</span> ((ch=getopt(argc, argv, optstring)) != EOF) {
	<span class="enscript-keyword">switch</span> (ch) {
	<span class="enscript-keyword">case</span> <span class="enscript-string">'a'</span>:
	    aflag = 1;
	    set_default_flag = 0;
	    flag_count++;
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'A'</span>:
	    Aflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'b'</span>:
	    bflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'c'</span>:
	    cflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'d'</span>:
	    dflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'g'</span>:
	    gflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'k'</span>:
	    kflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'m'</span>:
	    mflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'n'</span>:
	    nflag= 1;
	    <span class="enscript-keyword">if</span> (!strncmp(optarg, <span class="enscript-string">&quot;PPP&quot;</span>, 3))
		network_mode |= NET_PPP_MODE;
	    <span class="enscript-keyword">else</span> <span class="enscript-keyword">if</span> (!strncmp(optarg, <span class="enscript-string">&quot;DEV&quot;</span>, 3))
		network_mode |= NET_DEV_MODE;
	    <span class="enscript-keyword">else</span> <span class="enscript-keyword">if</span> (!strncmp(optarg, <span class="enscript-string">&quot;EDEV&quot;</span>, 4))
		network_mode |= NET_EDEV_MODE;
	    <span class="enscript-keyword">else</span>
		exit_usage();
	    set_default_flag = 0;
	    flag_count++;
	    <span class="enscript-keyword">break</span>;	    
	<span class="enscript-keyword">case</span> <span class="enscript-string">'p'</span>:
	    pflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'q'</span>:
	    qflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'r'</span>:
	    rflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'u'</span>:
	    uflag= 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'v'</span>:
	    vflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'w'</span>:
	    wflag = 1;
	    set_default_flag = 0;
	    flag_count++;
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'y'</span>:
	    yflag = 1;
	    set_default_flag = 0;
	    flag_count++;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'o'</span>:
	    <span class="enscript-comment">/* open the output file */</span>
	    oflag = 1;
	    outfile=optarg;
	    (<span class="enscript-type">void</span>)open_output_file(outfile);	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'e'</span>:  <span class="enscript-comment">/* eflag */</span>
	    end_time = convert_hms(optarg);
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'f'</span>:
	    fflag = 1;
	    infile=optarg;	    
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'i'</span>:
	    iflag = 1;
	    iseconds=atoi(optarg);
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-string">'s'</span>:
	    start_time = convert_hms(optarg);
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-reference">default</span>:
	    exit_usage();
	    <span class="enscript-keyword">break</span>;
	}
    }

    <span class="enscript-comment">/* setup default uflag option */</span>
    <span class="enscript-keyword">if</span> (Aflag)
    {
	dflag = gflag = pflag = uflag = 1;
	<span class="enscript-keyword">if</span> (!nflag)
	{
	    <span class="enscript-comment">/*
	     * Add network stats to the load
	     * but avoid PPP data by default.
	     */</span>
	    nflag = 1;
	    network_mode = NET_DEV_MODE | NET_EDEV_MODE;;
	}
	flag_count = 2;	  <span class="enscript-comment">/* triggers column headings */</span>
    }
    <span class="enscript-keyword">else</span> <span class="enscript-keyword">if</span> (set_default_flag)
    {
	uflag=1;
	flag_count++;
    }

    <span class="enscript-keyword">if</span> (nflag)
    {
	<span class="enscript-keyword">if</span> (network_mode &amp; NET_PPP_MODE)
	{
	    <span class="enscript-keyword">if</span> (!(network_mode &amp; NET_DEV_MODE) &amp;&amp;
	      !(network_mode &amp; NET_EDEV_MODE))
	    {
		<span class="enscript-comment">/* set defaults */</span>
		network_mode |= NET_DEV_MODE;
		network_mode |= NET_EDEV_MODE;
		flag_count++;
	    }
	}
    }

    argc -= optind;
    argv += optind;

    <span class="enscript-comment">/* set up signal handlers */</span>
    signal(SIGINT,  exit_average);
    signal(SIGQUIT, exit_average);
    signal(SIGHUP,  exit_average);
    signal(SIGTERM, exit_average); 

    <span class="enscript-keyword">if</span> (optstringval == 1)
    {
	<span class="enscript-comment">/* expecting a time interval */</span>
	
	<span class="enscript-type">char</span> *p;

	<span class="enscript-keyword">if</span> (argc &gt;= 1)
	{
	    errno = 0;
	    t_interval = strtol(argv[0], &amp;p, 0);
	    t_intervalp = argv[0];
	    <span class="enscript-keyword">if</span> (errno || (*p != <span class="enscript-string">'\0'</span>) || t_interval &lt;= 0 )
		exit_usage();
	    <span class="enscript-keyword">if</span> (argc &gt;= 2)
	    {
		errno=0;
		n_samples = strtol(argv[1], &amp;p, 0);
		n_samplesp = argv[1];
		<span class="enscript-keyword">if</span> (errno || (*p != <span class="enscript-string">'\0'</span>) || n_samples &lt;= 0)
		    exit_usage();
	    }
	}
    }

    <span class="enscript-comment">/* where does the input come from */</span>
    <span class="enscript-keyword">if</span> (fflag)
    {
	(<span class="enscript-type">void</span>)open_input_file(infile);
    }
    <span class="enscript-keyword">else</span> <span class="enscript-keyword">if</span> (optstringval == 2)
    {
	<span class="enscript-comment">/*
	 * Create a filename of the form /var/log/sa/sadd
	 * where &quot;dd&quot; is the date of the month
	 */</span>
	curr_time = time((time_t *)0);        <span class="enscript-comment">/* returns time in seconds */</span>

	<span class="enscript-comment">/*
	  timebuf will be a 26-character string of the form:
	  Thu Nov 24 18:22:48 1986\n\0
	*/</span>

	ctime_r(&amp;curr_time, timebuf);
	strncpy(filenamebuf, <span class="enscript-string">&quot;/var/log/sa/sa&quot;</span>, 14);
	strncpy(&amp;filenamebuf[14], &amp;timebuf[8], 2);
	<span class="enscript-keyword">if</span> (filenamebuf[14] == <span class="enscript-string">' '</span>)
	    filenamebuf[14] = <span class="enscript-string">'0'</span>;
	filenamebuf[16]=<span class="enscript-string">'\0'</span>;
	infile = filenamebuf;
	(<span class="enscript-type">void</span>)open_input_file(infile);
    }
    <span class="enscript-keyword">else</span> <span class="enscript-keyword">if</span> (optstringval == 1)
    {
	<span class="enscript-comment">/* launch sadc */</span>
	<span class="enscript-keyword">if</span> (pipe(fd) == -1)
	{
	    fprintf(stderr, <span class="enscript-string">&quot;sar: pipe(2) failed, errno = (%d)\n&quot;</span>,errno);
	    exit(1);
	}

	<span class="enscript-keyword">if</span> ((pid=fork()) == 0)
	{
#<span class="enscript-reference">if</span> 0
	    <span class="enscript-type">int</span> efd;
#<span class="enscript-reference">endif</span>
	    <span class="enscript-type">int</span> fdlimit = getdtablesize();
	    
            <span class="enscript-comment">/* This is the child */</span>
	    <span class="enscript-comment">/* Close all file descriptors except the one we need */</span>
	    
	    <span class="enscript-keyword">for</span> (i=0; i &lt; fdlimit; i++) {
		<span class="enscript-keyword">if</span> ((i != fd[0]) &amp;&amp; (i != fd[1]))
		    (<span class="enscript-type">void</span>)close(i);
	    }
#<span class="enscript-reference">if</span> 0
	    efd = open(<span class="enscript-string">&quot;/tmp/errlog&quot;</span>, O_CREAT|O_APPEND|O_RDWR, 0666);
	    <span class="enscript-keyword">if</span> (dup2(efd,2) == -1) {
		exit(1);
	    }
#<span class="enscript-reference">endif</span>
	    <span class="enscript-comment">/* Dup the two file descriptors to stdin and stdout */</span>
	    <span class="enscript-keyword">if</span> (dup2(fd[0],0) == -1) {
		exit(1);
	    }
	    <span class="enscript-keyword">if</span> (dup2(fd[1],1) == -1) {
		exit(1);
	    }
	    <span class="enscript-comment">/* Exec the child process */</span>
	    <span class="enscript-keyword">if</span> (network_mode &amp; NET_PPP_MODE)
		execl(<span class="enscript-string">&quot;/usr/lib/sa/sadc&quot;</span>, <span class="enscript-string">&quot;sadc&quot;</span>, sadc_mflagp, sadc_ppp_modep, t_intervalp, n_samplesp, NULL);
	    <span class="enscript-keyword">else</span>
		execl(<span class="enscript-string">&quot;/usr/lib/sa/sadc&quot;</span>, <span class="enscript-string">&quot;sadc&quot;</span>, t_intervalp, n_samplesp, NULL);		    

	    perror(<span class="enscript-string">&quot;execlp sadc&quot;</span>);
	    exit(2); <span class="enscript-comment">/* This call of exit(2) should never be reached... */</span>
	}
	<span class="enscript-keyword">else</span>
	{	 <span class="enscript-comment">/* This is the parent */</span>
	    <span class="enscript-keyword">if</span> (pid == -1) {
		fprintf(stderr, <span class="enscript-string">&quot;sar: fork(2) failed, errno = (%d)\n&quot;</span>,errno);
		exit(1);
	    }
	    close (fd[1]);  <span class="enscript-comment">/* parent does not write to the pipe */</span>
	    ifd = fd[0];    <span class="enscript-comment">/* parent will read from the pipe */</span>
	}	
    }
    <span class="enscript-keyword">else</span>
    {
	<span class="enscript-comment">/* we're confused about source of input data - bail out */</span>
	fprintf(stderr, <span class="enscript-string">&quot;sar: no input file recognized\n&quot;</span>);
	exit_usage();
    }

    <span class="enscript-comment">/* start reading input data and format the output */</span>
    (<span class="enscript-type">void</span>)do_main_workloop();
    (<span class="enscript-type">void</span>)exit_average();
    exit(0);
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">exit_usage</span>()
{
    fprintf(stderr, <span class="enscript-string">&quot;\n%s\n\n&quot;</span>, optionstring1_usage);
    fprintf(stderr, <span class="enscript-string">&quot;%s\n&quot;</span>,   optionstring2_usage);
    exit(EXIT_FAILURE);
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">open_output_file</span>(<span class="enscript-type">char</span> *path)
{
    <span class="enscript-keyword">if</span> ((ofd = open(path, O_CREAT|O_APPEND|O_TRUNC|O_WRONLY, 0664)) == -1 )
    {
	<span class="enscript-comment">/* failed to open path */</span>
	fprintf(stderr, <span class="enscript-string">&quot;sar: failed to open output file [%s]\n&quot;</span>, path);
	exit_usage();
    }
}


<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">open_input_file</span>(<span class="enscript-type">char</span> *path)
{
    <span class="enscript-keyword">if</span> ((ifd = open(path, O_RDONLY, 0)) == -1)
    {
	<span class="enscript-comment">/* failed to open path */</span>
	fprintf(stderr, <span class="enscript-string">&quot;sar: failed to open input file [%d][%s]\n&quot;</span>, ifd, path);
	exit_usage();
    }
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">read_record_hdr</span>(hdr, writeflag)
    <span class="enscript-type">struct</span> record_hdr *hdr;
    <span class="enscript-type">int</span> writeflag; 
{
    errno = 0;
    <span class="enscript-type">int</span> num = 0;
    <span class="enscript-type">int</span> n = 0;
    size_t size = 0;

    size = <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> record_hdr);

    <span class="enscript-keyword">while</span> (size)
    {
	num = read(ifd, &amp;hdr[n], size);	
	<span class="enscript-keyword">if</span> (num &gt; 0)
	{
	    n += num;
	    size -= num;
	}
	<span class="enscript-keyword">else</span> <span class="enscript-keyword">if</span> (num == 0)
	    exit_average();
	<span class="enscript-keyword">else</span>
	{
	    fprintf(stderr, <span class="enscript-string">&quot;sar: read_record_data failed, errno=%d num=%d, size=%d\n&quot;</span>, (<span class="enscript-type">int</span>)errno, (<span class="enscript-type">int</span>)num, (<span class="enscript-type">int</span>)size);
	    exit(EXIT_FAILURE);
	}
    }
    
    <span class="enscript-keyword">if</span> (oflag &amp;&amp; writeflag)
	write_record_hdr(hdr);
    
    <span class="enscript-keyword">return</span>;	
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">read_record_data</span>(buf, size, writeflag)
    <span class="enscript-type">char</span> *  buf;
    size_t  size;
    <span class="enscript-type">int</span>     writeflag;
{
    errno = 0;
    size_t num = 0;
    size_t n = 0;

    <span class="enscript-keyword">while</span> (size)
    {
	num = read(ifd, &amp;buf[n], size);	
	<span class="enscript-keyword">if</span> (num &gt; 0)
	{
	    n += num;
	    size -= num;
	}
	<span class="enscript-keyword">else</span> <span class="enscript-keyword">if</span> (num == 0)   <span class="enscript-comment">/* EOF */</span>
	    exit_average();	
	<span class="enscript-keyword">else</span>
	{
	    fprintf(stderr, <span class="enscript-string">&quot;sar: read_record_data failed, errno=%d num=%d, size=%d\n&quot;</span>, (<span class="enscript-type">int</span>)errno, (<span class="enscript-type">int</span>)num, (<span class="enscript-type">int</span>)size);
	    exit(EXIT_FAILURE);
	}
    }

    <span class="enscript-keyword">if</span> (oflag &amp;&amp; writeflag)
	write_record_data(buf, n);
    
    <span class="enscript-keyword">return</span>;
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">write_record_hdr</span>(hdr)
    <span class="enscript-type">struct</span> record_hdr *hdr;
{
    errno = 0;
    <span class="enscript-type">int</span> num;
    
    <span class="enscript-keyword">if</span> ((num = write(ofd, hdr, <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> record_hdr))) == -1)
    {
	fprintf(stderr, <span class="enscript-string">&quot;sar: write_record_hdr failed, errno=%d\n&quot;</span>, errno);	
	exit(EXIT_FAILURE);
    }
    <span class="enscript-keyword">return</span>;
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">write_record_data</span>(<span class="enscript-type">char</span> *buf, size_t nbytes)
{
    errno = 0;
    <span class="enscript-type">int</span> num;
    <span class="enscript-keyword">if</span> ((num = write(ofd, buf, nbytes)) == -1)
    {
	fprintf(stderr, <span class="enscript-string">&quot;sar: write_record_data failed, errno=%d\n&quot;</span>, errno);
	exit(EXIT_FAILURE);
    }
    <span class="enscript-keyword">return</span>;	
}

<span class="enscript-comment">/*
 * Convert a string of one of the forms
 *      hh   hh:mm     hh:mm:ss
 * into the number of seconds.
 * exit on error
*/</span>

<span class="enscript-type">static</span> time_t
<span class="enscript-function-name">convert_hms</span>(string)
    <span class="enscript-type">char</span> *string;
{
    <span class="enscript-type">int</span> hh = 0;   <span class="enscript-comment">/* hours */</span>
    <span class="enscript-type">int</span> mm = 0;   <span class="enscript-comment">/* minutes */</span>
    <span class="enscript-type">int</span> ss = 0;   <span class="enscript-comment">/* seconds */</span>
    time_t seconds;
    time_t timestamp;
    <span class="enscript-type">struct</span> tm *tm;
    <span class="enscript-type">int</span> i;

    <span class="enscript-keyword">if</span> (string == NULL || *string == <span class="enscript-string">'\0'</span>)
	<span class="enscript-keyword">goto</span> <span class="enscript-reference">convert_err</span>;

    <span class="enscript-keyword">for</span> (i=0; string[i] != <span class="enscript-string">'\0'</span>; i++)
    {
	<span class="enscript-keyword">if</span> ((!isdigit(string[i])) &amp;&amp; (string[i] != <span class="enscript-string">':'</span>))
	{
	    <span class="enscript-keyword">goto</span> <span class="enscript-reference">convert_err</span>;
	}
    }

    <span class="enscript-keyword">if</span> (sscanf(string, <span class="enscript-string">&quot;%d:%d:%d&quot;</span>, &amp;hh, &amp;mm, &amp;ss) != 3)
    {
	<span class="enscript-keyword">if</span> (sscanf(string, <span class="enscript-string">&quot;%d:%d&quot;</span>, &amp;hh, &amp;mm) != 2)
	{
	    <span class="enscript-keyword">if</span> (sscanf(string, <span class="enscript-string">&quot;%d&quot;</span>, &amp;hh) != 1)
	    {
		<span class="enscript-keyword">goto</span> <span class="enscript-reference">convert_err</span>;
	    }
	}
    }

    <span class="enscript-keyword">if</span> (hh &lt; 0 || hh &gt;= HOURS_PER_DAY ||
      mm &lt; 0 || mm &gt;= MINS_PER_HOUR ||
      ss &lt; 0 || ss &gt; SECS_PER_MIN)
    {
	<span class="enscript-keyword">goto</span> <span class="enscript-reference">convert_err</span>;
    }

    seconds = ((((hh * MINS_PER_HOUR) + mm) * SECS_PER_MIN) + ss);
    timestamp = time((time_t *)0);
    tm=localtime(&amp;timestamp);
    seconds -= tm-&gt;tm_gmtoff;
    
    <span class="enscript-keyword">return</span>(seconds);   
    
    <span class="enscript-reference">convert_err</span>:
    fprintf(stderr, <span class="enscript-string">&quot;sar: time format usage is hh[:mm[:ss]]\n&quot;</span>);
    exit_usage();
    <span class="enscript-keyword">return</span>(0);
}


<span class="enscript-comment">/*
 * Use ctime_r to convert a time value into
 * a 26-character string of the form:
 *
 * Thu Nov 24 18:22:48 1986\n\0
 */</span>

<span class="enscript-type">static</span> <span class="enscript-type">char</span> *
<span class="enscript-function-name">get_hms_string</span>(tdata, tbuf)
    time_t tdata;
    <span class="enscript-type">char</span> *tbuf;
{
    time_t t;
    <span class="enscript-type">char</span> *p;

    t = tdata;
    ctime_r(&amp;t, tbuf);
    p=&amp;tbuf[11];
    tbuf[19] = 0;

    <span class="enscript-keyword">return</span>(p);
}
    

<span class="enscript-comment">/* sample set flags */</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">INIT_SET</span>   0
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">PRINT_SET</span>  1
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">PRINT_AVG</span>  2

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">do_main_workloop</span>()
{
    <span class="enscript-type">struct</span> record_hdr hdr;
    time_t cur_timestamp = 0;	<span class="enscript-comment">/* seconds - Coordinated Universal Time */</span>
    time_t next_timestamp = 0;  <span class="enscript-comment">/* seconds - Coordinated Universal Time */</span>

    <span class="enscript-keyword">if</span> (!find_restart_header(&amp;hdr))
	exit(1);

    cur_timestamp = hdr.rec_timestamp;

    <span class="enscript-comment">/* convert sflag's start_time from 24 hour clock time to UTC seconds */</span>
    <span class="enscript-keyword">if</span> (start_time  &lt; (cur_timestamp % SECS_PER_DAY))
	start_time = cur_timestamp;
    <span class="enscript-keyword">else</span>
	start_time += cur_timestamp - (cur_timestamp % SECS_PER_DAY);

    <span class="enscript-comment">/* convert end_time, from 24 hour clock time to UTC seconds */</span>
    <span class="enscript-keyword">if</span> (end_time != 0)
	end_time += cur_timestamp - (cur_timestamp % SECS_PER_DAY);

#<span class="enscript-reference">if</span> 0
	fprintf(stderr, <span class="enscript-string">&quot;start = %ld, end = %ld, cur=%ld, [24hour - %ld]\n&quot;</span>,
	  start_time, end_time, cur_timestamp,(cur_timestamp % SECS_PER_DAY));
#<span class="enscript-reference">endif</span>

    <span class="enscript-keyword">while</span> (cur_timestamp &lt; start_time)
    {
	bypass_sample_set(&amp;hdr, cur_timestamp);
	cur_timestamp = hdr.rec_timestamp;
    }

    next_timestamp = cur_timestamp + iseconds;
    print_all_column_headings(cur_timestamp);
    read_sample_set(INIT_SET, cur_timestamp, &amp;hdr);
    cur_timestamp = hdr.rec_timestamp;    

    <span class="enscript-keyword">while</span> ((end_time == 0) || (next_timestamp &lt; end_time))
    {
	<span class="enscript-keyword">if</span> (cur_timestamp &lt; next_timestamp)
	{
	    bypass_sample_set (&amp;hdr, cur_timestamp);
	    cur_timestamp = hdr.rec_timestamp;
	}
	<span class="enscript-keyword">else</span>
	{
	    <span class="enscript-comment">/* need to know the seconds interval when printing averages */</span>
	    <span class="enscript-keyword">if</span> (avg_interval == 0)
	    {
		<span class="enscript-keyword">if</span> (iseconds)
		    avg_interval = iseconds;
		<span class="enscript-keyword">else</span>
		    avg_interval = cur_timestamp - next_timestamp;
	    }
	    next_timestamp = cur_timestamp + iseconds;	    
	    read_sample_set(PRINT_SET, cur_timestamp, &amp;hdr);
	    cur_timestamp = hdr.rec_timestamp;	    
	}
    }
    exit_average();
}


<span class="enscript-comment">/*
 * Find and fill in a restart header.  We don't write
 * the binary data when looking for SAR_RESTART.
 * Return:  1 on success
 *          0 on failure
 */</span>
<span class="enscript-type">static</span> <span class="enscript-type">int</span>
<span class="enscript-function-name">find_restart_header</span> (ret_hdr)
    <span class="enscript-type">struct</span> record_hdr *ret_hdr;
{
    <span class="enscript-type">struct</span> record_hdr hdr;
    <span class="enscript-type">int</span> bufsize = 0;
    <span class="enscript-type">char</span> *buf = NULL;

    errno = 0;
    
    <span class="enscript-reference">restart_loop</span>:
    read_record_hdr(&amp;hdr, FALSE);   <span class="enscript-comment">/* exits on error */</span>
    
    <span class="enscript-keyword">if</span> (hdr.rec_type == SAR_RESTART)
    {
	*ret_hdr = hdr;
	<span class="enscript-keyword">if</span> (oflag)
	    write_record_hdr(&amp;hdr);   <span class="enscript-comment">/* writes the RESTART record */</span>
	<span class="enscript-keyword">if</span> (buf)
	    free(buf);
	<span class="enscript-keyword">return</span>(1);
    }

    <span class="enscript-comment">/*
     * not the record we want...
     * read past data and try again
     */</span>
    <span class="enscript-keyword">if</span> (hdr.rec_count)
    {
	<span class="enscript-keyword">if</span> (fflag)
	{ <span class="enscript-comment">/* seek past data in the file */</span>
	    <span class="enscript-keyword">if</span> ((lseek(ifd, (hdr.rec_count * hdr.rec_size), SEEK_CUR)) == -1)
	    {
		<span class="enscript-comment">/*exit on error */</span>
		fprintf(stderr, <span class="enscript-string">&quot;sar: lseek failed, errno=%d\n&quot;</span>, errno);
		exit(EXIT_FAILURE);
	    }
	    
	}	    
	<span class="enscript-comment">/* compute data size - malloc a new buf if it's not big enough */</span>
	<span class="enscript-keyword">else</span> 
	{
	    <span class="enscript-comment">/* have to read from the pipe */</span>
	    <span class="enscript-keyword">if</span> (bufsize &lt; (hdr.rec_count * hdr.rec_size))
	    {
		<span class="enscript-keyword">if</span> (buf)
		    free(buf);
		bufsize = hdr.rec_count * hdr.rec_size;
		<span class="enscript-keyword">if</span>((buf = (<span class="enscript-type">char</span> *)malloc(bufsize)) == NULL)
		{
		    fprintf(stderr, <span class="enscript-string">&quot;sar: malloc failed\n&quot;</span>);
		    <span class="enscript-keyword">return</span>(0);
		}
	    }
	    <span class="enscript-comment">/* exits on error */</span>
	    read_record_data(buf, (hdr.rec_count * hdr.rec_size), FALSE);
	}
    }
    <span class="enscript-keyword">goto</span> <span class="enscript-reference">restart_loop</span>;
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">print_all_column_headings</span>(timestamp)
    time_t timestamp;
{
    <span class="enscript-type">char</span> timebuf[26];
    <span class="enscript-type">char</span> *timebufp;

    timebufp = get_hms_string (timestamp, timebuf);

    <span class="enscript-keyword">if</span> (uflag) <span class="enscript-comment">/* print cpu headers */</span>
	print_column_heading(SAR_CPU, timebufp, 0);

    <span class="enscript-keyword">if</span> (gflag) 	<span class="enscript-comment">/* print page-out activity */</span>
	print_column_heading(SAR_VMSTAT, timebufp, 0);

    <span class="enscript-keyword">if</span> (pflag ) <span class="enscript-comment">/* print page-in activity */</span>	
	print_column_heading(SAR_VMSTAT, timebufp, 1);

    <span class="enscript-keyword">if</span> (dflag) <span class="enscript-comment">/* print drive stats */</span>
	print_column_heading(SAR_DRIVESTATS, timebufp, 0);

    <span class="enscript-keyword">if</span> (nflag) <span class="enscript-comment">/* print network stats */</span>
    {
	<span class="enscript-keyword">if</span> (network_mode &amp; NET_DEV_MODE)
	    print_column_heading(SAR_NETSTATS, timebufp, NET_DEV_MODE);	    

	<span class="enscript-keyword">if</span> (network_mode &amp; NET_EDEV_MODE)
	    print_column_heading(SAR_NETSTATS, timebufp, NET_EDEV_MODE);	    	    
    }
}	


<span class="enscript-comment">/*
 * Find and fill in a timestamp header.
 * Write the binary data when looking for SAR_TIMESTAMP
 * Don't do anything with the data, just read past it.
 * Return:  1 on success
 *          0 on failure
 */</span>
<span class="enscript-type">static</span> <span class="enscript-type">int</span>
<span class="enscript-function-name">bypass_sample_set</span> (ret_hdr, timestamp)
    <span class="enscript-type">struct</span> record_hdr *ret_hdr;
    time_t timestamp;
{
    <span class="enscript-type">struct</span> record_hdr hdr;
    <span class="enscript-type">int</span> bufsize = 0;
    <span class="enscript-type">char</span> *buf = NULL;

    <span class="enscript-reference">bypass_loop</span>:
    read_record_hdr(&amp;hdr, TRUE);   <span class="enscript-comment">/* exits on error */</span>
    
    <span class="enscript-keyword">if</span> (hdr.rec_type == SAR_TIMESTAMP)
    {
	*ret_hdr = hdr;
	<span class="enscript-keyword">if</span> (buf)
	    free(buf);
	<span class="enscript-keyword">return</span>(1);
    }

    <span class="enscript-comment">/*
     * not the record we want...
     * read past data and try again
     */</span>
    <span class="enscript-keyword">if</span> (hdr.rec_count)
    {
	<span class="enscript-keyword">if</span> (fflag &amp;&amp; !oflag)
	{
	    <span class="enscript-comment">/*
	     * we're reading from a file and we don't have to write the
	     * binary data so seek past data in the file
	     */</span>
	    errno = 0;
	    <span class="enscript-keyword">if</span> ((lseek(ifd, (hdr.rec_count * hdr.rec_size), SEEK_CUR)) == -1)
	    {
		<span class="enscript-comment">/*exit on error */</span>
		fprintf(stderr, <span class="enscript-string">&quot;sar: lseek failed, errno=%d\n&quot;</span>, errno);
		exit(EXIT_FAILURE);
	    }	    
	}
	<span class="enscript-keyword">else</span>
	{
	    <span class="enscript-comment">/*
	     * We end up here when reading from pipe.
	     * malloc a new buffer if current is not big enough
	     */</span>
	    <span class="enscript-keyword">if</span> (bufsize &lt; (hdr.rec_count * hdr.rec_size))
	    {
		<span class="enscript-keyword">if</span> (buf)
		    free(buf);
		bufsize = hdr.rec_count * hdr.rec_size;
		<span class="enscript-keyword">if</span>((buf = (<span class="enscript-type">char</span> *)malloc(bufsize)) == NULL)
		{
		    fprintf(stderr, <span class="enscript-string">&quot;sar: malloc failed\n&quot;</span>);
		    exit(EXIT_FAILURE);
		}
	    }

	    <span class="enscript-comment">/* exits on error */</span>
	    read_record_data(buf, (hdr.rec_count * hdr.rec_size), TRUE);
	}
    } <span class="enscript-comment">/* end if hdr.rec_count */</span>
    <span class="enscript-keyword">goto</span> <span class="enscript-reference">bypass_loop</span>;
}


<span class="enscript-comment">/*
 * INIT_SET: This initializes the first sample for each type.
 * PRINT_SET: This read, compute and print out sample data.
 */</span>
<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">read_sample_set</span>(flag, timestamp, ret_hdr)
    <span class="enscript-type">int</span> flag;
    time_t timestamp;
    <span class="enscript-type">struct</span> record_hdr *ret_hdr;
{
    <span class="enscript-type">struct</span> record_hdr hdr;
    <span class="enscript-type">char</span> timebuf[26];
    <span class="enscript-type">char</span> *timebufp;
    <span class="enscript-type">char</span> *indent_string;
    <span class="enscript-type">char</span> *indent_string_wide;
    <span class="enscript-type">char</span> *indent_string_narrow;
    <span class="enscript-type">int</span> sar_cpu = 0;
    <span class="enscript-type">int</span> sar_vmstat=0;
    <span class="enscript-type">int</span> sar_drivestats=0;
    <span class="enscript-type">int</span> sar_drivepath=0;
    <span class="enscript-type">int</span> sar_netstats = 0;

    indent_string_wide = <span class="enscript-string">&quot;          &quot;</span>;
    indent_string_narrow = <span class="enscript-string">&quot;  &quot;</span>;    
    indent_string = indent_string_narrow;
    
    read_record_hdr(&amp;hdr, TRUE);

    <span class="enscript-keyword">while</span> (hdr.rec_type != SAR_TIMESTAMP)
    {
	<span class="enscript-keyword">switch</span> (hdr.rec_type)
	{
	<span class="enscript-keyword">case</span> <span class="enscript-reference">SAR_CPU</span>:
	    sar_cpu = get_cpu_sample(flag, &amp;hdr);
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-reference">SAR_VMSTAT</span>:
	    sar_vmstat=get_vmstat_sample(flag, &amp;hdr);
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-reference">SAR_DRIVEPATH</span>:
	  sar_drivepath = get_drivepath_sample(flag, &amp;hdr);
	  <span class="enscript-keyword">if</span> (sar_drivepath &lt; 0)
	      fprintf(stderr, <span class="enscript-string">&quot;sar: drivepath sync code error %d\n&quot;</span>, sar_drivepath);
	  <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-reference">SAR_DRIVESTATS</span>:
	    sar_drivestats = get_drivestats_sample(flag, &amp;hdr);
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-keyword">case</span> <span class="enscript-reference">SAR_NETSTATS</span>:
	    sar_netstats = get_netstats_sample(flag, &amp;hdr);
	    <span class="enscript-keyword">break</span>;
	<span class="enscript-reference">default</span>:
	    <span class="enscript-keyword">break</span>;
	}

	read_record_hdr(&amp;hdr, TRUE);
    }

    <span class="enscript-comment">/* return the timestamp header */</span>
    *ret_hdr = hdr;

    <span class="enscript-keyword">if</span> (flag == PRINT_SET)
    {
	avg_counter++;
	timebufp = get_hms_string(timestamp, timebuf);

	<span class="enscript-keyword">if</span> (uflag &amp;&amp; sar_cpu)
	    print_cpu_sample(timebufp);

	<span class="enscript-keyword">if</span>((gflag || pflag) &amp;&amp; sar_vmstat)
	    print_vmstat_sample(timebufp);

	<span class="enscript-keyword">if</span> (dflag &amp;&amp; sar_drivestats)
	    print_drivestats_sample(timebufp);

	<span class="enscript-keyword">if</span> (nflag &amp;&amp; sar_netstats)
	    print_netstats_sample(timebufp);
    }
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">skip_data</span>(bufsize)
    <span class="enscript-type">int</span> bufsize;
{
    <span class="enscript-type">char</span> *buf = NULL;
    
    <span class="enscript-keyword">if</span> (fflag)
    {
        <span class="enscript-comment">/* seek past data in the file */</span>
	<span class="enscript-keyword">if</span> ((lseek(ifd, bufsize, SEEK_CUR) == -1))
	{
	    <span class="enscript-comment">/*exit on error */</span>
	    fprintf(stderr, <span class="enscript-string">&quot;sar: lseek failed, errno=%d\n&quot;</span>, errno);
	    exit(EXIT_FAILURE);
	}
    }	    
    <span class="enscript-keyword">else</span> 
    {
	<span class="enscript-comment">/* have to read from the pipe */</span>
	<span class="enscript-keyword">if</span>((buf = (<span class="enscript-type">char</span> *)malloc(bufsize)) == NULL)
	{
	    fprintf(stderr, <span class="enscript-string">&quot;sar: malloc failed\n&quot;</span>);
	    exit(EXIT_FAILURE);
	}
	<span class="enscript-comment">/* even though we skip this data, we still write it if necessary */</span>
	read_record_data(buf, bufsize, TRUE);
    }
    <span class="enscript-keyword">if</span> (buf)
	free(buf);
    
    <span class="enscript-keyword">return</span>;
}

<span class="enscript-type">static</span> <span class="enscript-type">int</span>
<span class="enscript-function-name">get_cpu_sample</span>(flag, hdr)
    <span class="enscript-type">int</span> flag;
    <span class="enscript-type">struct</span> record_hdr *hdr;
{
    <span class="enscript-type">int</span>  datasize;

    datasize = hdr-&gt;rec_count * hdr-&gt;rec_size;
    
    <span class="enscript-keyword">if</span> (datasize != <span class="enscript-keyword">sizeof</span>(host_cpu_load_info_data_t))
    {
	<span class="enscript-comment">/* read past the data but don't do anything with it */</span>
	skip_data(datasize);
	<span class="enscript-keyword">return</span>(0);
    }

    read_record_data ((<span class="enscript-type">char</span> *)&amp;cur_cpuload, (<span class="enscript-type">int</span>)<span class="enscript-keyword">sizeof</span>(host_cpu_load_info_data_t), TRUE );

    <span class="enscript-keyword">if</span> (flag == INIT_SET)
    {
	prev_cpuload = cur_cpuload;
	bzero(&amp;avg_cpuload, <span class="enscript-keyword">sizeof</span>(avg_cpuload));
    }
    <span class="enscript-keyword">return</span>(1);
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">print_cpu_sample</span>(timebufptr)
    <span class="enscript-type">char</span> * timebufptr;
{

    <span class="enscript-type">double</span> time;

    time = 0.0;
    cur_cpuload.cpu_ticks[CPU_STATE_USER]
      -= prev_cpuload.cpu_ticks[CPU_STATE_USER];
    
    prev_cpuload.cpu_ticks[CPU_STATE_USER]
      += cur_cpuload.cpu_ticks[CPU_STATE_USER];
	
    time += cur_cpuload.cpu_ticks[CPU_STATE_USER];

    cur_cpuload.cpu_ticks[CPU_STATE_NICE]
      -= prev_cpuload.cpu_ticks[CPU_STATE_NICE];
    
    prev_cpuload.cpu_ticks[CPU_STATE_NICE]
      += cur_cpuload.cpu_ticks[CPU_STATE_NICE];
	
    time += cur_cpuload.cpu_ticks[CPU_STATE_NICE];
	
    cur_cpuload.cpu_ticks[CPU_STATE_SYSTEM]
      -= prev_cpuload.cpu_ticks[CPU_STATE_SYSTEM];
	
    prev_cpuload.cpu_ticks[CPU_STATE_SYSTEM]
      += cur_cpuload.cpu_ticks[CPU_STATE_SYSTEM];
	
    time += cur_cpuload.cpu_ticks[CPU_STATE_SYSTEM];
	
    cur_cpuload.cpu_ticks[CPU_STATE_IDLE]
      -= prev_cpuload.cpu_ticks[CPU_STATE_IDLE];
	
    prev_cpuload.cpu_ticks[CPU_STATE_IDLE]
      += cur_cpuload.cpu_ticks[CPU_STATE_IDLE];
	
    time += cur_cpuload.cpu_ticks[CPU_STATE_IDLE];

    avg_cpuload.cpu_ticks[CPU_STATE_USER] += rint(100. * cur_cpuload.cpu_ticks[CPU_STATE_USER]
      / (time ? time : 1));

    avg_cpuload.cpu_ticks[CPU_STATE_NICE] += rint(100. * cur_cpuload.cpu_ticks[CPU_STATE_NICE]
      / (time ? time : 1));

    avg_cpuload.cpu_ticks[CPU_STATE_SYSTEM] += rint(100. * cur_cpuload.cpu_ticks[CPU_STATE_SYSTEM]
      / (time ? time : 1));
    
    avg_cpuload.cpu_ticks[CPU_STATE_IDLE] += rint(100. * cur_cpuload.cpu_ticks[CPU_STATE_IDLE]
      / (time ? time : 1));

    <span class="enscript-keyword">if</span>(flag_count &gt; 1)
	print_column_heading(SAR_CPU, timebufptr, 0);

    fprintf(stdout, <span class="enscript-string">&quot;%s%5.0f   &quot;</span>, timebufptr,
      rint(100. * cur_cpuload.cpu_ticks[CPU_STATE_USER]
      / (time ? time : 1)));
	
    fprintf(stdout, <span class="enscript-string">&quot;%4.0f   &quot;</span>,
      rint(100. * cur_cpuload.cpu_ticks[CPU_STATE_NICE]
      / (time ? time : 1)));

    fprintf(stdout, <span class="enscript-string">&quot;%4.0f   &quot;</span>,
      rint(100. * cur_cpuload.cpu_ticks[CPU_STATE_SYSTEM]
      / (time ? time : 1)));
	
    fprintf(stdout, <span class="enscript-string">&quot;%4.0f\n&quot;</span>,
      rint(100. * cur_cpuload.cpu_ticks[CPU_STATE_IDLE]
      / (time ? time : 1)));
}

<span class="enscript-type">static</span> <span class="enscript-type">int</span>
<span class="enscript-function-name">get_vmstat_sample</span>(flag, hdr)
    <span class="enscript-type">int</span> flag;
    <span class="enscript-type">struct</span> record_hdr *hdr;
{
    <span class="enscript-type">int</span>  datasize;

    datasize = hdr-&gt;rec_count * hdr-&gt;rec_size;
    
    <span class="enscript-keyword">if</span> (datasize != <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> vm_statistics))
    {
	<span class="enscript-comment">/* read past the data but don't do anything with it */</span>
	skip_data(datasize);
	<span class="enscript-keyword">return</span>(0);
    }

    read_record_data ((<span class="enscript-type">char</span> *)&amp;cur_vmstat, (<span class="enscript-type">int</span>)<span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> vm_statistics), TRUE );

    <span class="enscript-keyword">if</span> (flag == INIT_SET)
    {
	prev_vmstat = cur_vmstat;
	bzero(&amp;avg_vmstat, <span class="enscript-keyword">sizeof</span>(avg_vmstat));
    }
    <span class="enscript-keyword">return</span>(1);
}


<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">print_vmstat_sample</span>(<span class="enscript-type">char</span> *timebufptr)
{

    cur_vmstat.faults -= prev_vmstat.faults;
    prev_vmstat.faults += cur_vmstat.faults;
    avg_vmstat.faults += cur_vmstat.faults;	

    cur_vmstat.cow_faults -= prev_vmstat.cow_faults;
    prev_vmstat.cow_faults += cur_vmstat.cow_faults;
    avg_vmstat.cow_faults += cur_vmstat.cow_faults;	

    cur_vmstat.zero_fill_count -= prev_vmstat.zero_fill_count;
    prev_vmstat.zero_fill_count += cur_vmstat.zero_fill_count;
    avg_vmstat.zero_fill_count += cur_vmstat.zero_fill_count;

    cur_vmstat.reactivations -= prev_vmstat.reactivations;
    prev_vmstat.reactivations += cur_vmstat.reactivations;
    avg_vmstat.reactivations += cur_vmstat.reactivations;	
	
    cur_vmstat.pageins -= prev_vmstat.pageins;
    prev_vmstat.pageins += cur_vmstat.pageins;
    avg_vmstat.pageins += cur_vmstat.pageins;	
	
    cur_vmstat.pageouts -= prev_vmstat.pageouts;
    prev_vmstat.pageouts += cur_vmstat.pageouts;
    avg_vmstat.pageouts += cur_vmstat.pageouts;


    <span class="enscript-keyword">if</span> (gflag)
    {
	<span class="enscript-keyword">if</span> (flag_count &gt; 1)
	    print_column_heading(SAR_VMSTAT, timebufptr, 0);
	fprintf(stdout, <span class="enscript-string">&quot;%s   %8.1f   \n&quot;</span>, timebufptr, (<span class="enscript-type">float</span>)((<span class="enscript-type">float</span>)cur_vmstat.pageouts/avg_interval));
    }
	
    <span class="enscript-keyword">if</span> (pflag)
    {
	<span class="enscript-keyword">if</span> (flag_count &gt; 1)
	    print_column_heading(SAR_VMSTAT, timebufptr, 1);
	fprintf(stdout, <span class="enscript-string">&quot;%s   %8.1f      %8.1f      %8.1f\n&quot;</span>, timebufptr,
	  (<span class="enscript-type">float</span>)((<span class="enscript-type">float</span>)cur_vmstat.pageins / avg_interval),
	  (<span class="enscript-type">float</span>)((<span class="enscript-type">float</span>)cur_vmstat.cow_faults/avg_interval),
	  (<span class="enscript-type">float</span>)((<span class="enscript-type">float</span>)cur_vmstat.faults/avg_interval));
    }
    fflush(stdout);
}

<span class="enscript-type">static</span> <span class="enscript-type">int</span>
<span class="enscript-function-name">get_drivestats_sample</span>(flag, hdr)
    <span class="enscript-type">int</span> flag;
    <span class="enscript-type">struct</span> record_hdr *hdr;
{
    <span class="enscript-type">struct</span> drivestats *databuf;
    <span class="enscript-type">struct</span> drivestats_report *dr;
    size_t  datasize;
    <span class="enscript-type">int</span>     datacount;
    <span class="enscript-type">int</span>     index;    
    <span class="enscript-type">int</span>     i;
    
    datasize = hdr-&gt;rec_count * hdr-&gt;rec_size;
    datacount = hdr-&gt;rec_count;
    
    <span class="enscript-keyword">if</span> (hdr-&gt;rec_size != <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> drivestats))
    {
	<span class="enscript-comment">/* something isn't right... read past the data but don't analyze it */</span>
	skip_data(datasize);
	<span class="enscript-keyword">return</span>(0);
    }

    <span class="enscript-comment">/* malloc read buffer */</span>
    <span class="enscript-keyword">if</span> ((databuf = (<span class="enscript-type">struct</span> drivestats *)malloc(datasize)) == NULL)
    {
	fprintf(stderr, <span class="enscript-string">&quot;sar: malloc failed\n&quot;</span>);
	exit (EXIT_FAILURE);
    }

    bzero(databuf, datasize);

    read_record_data ((<span class="enscript-type">char</span> *)databuf, datasize, TRUE );
    
    <span class="enscript-comment">/* clear all global current fields */</span>
    <span class="enscript-keyword">for</span>(dr = dr_head; dr; dr=(<span class="enscript-type">struct</span> drivestats_report *)dr-&gt;next)
    {
	dr-&gt;present = 0;
	dr-&gt;cur_Reads = 0;
	dr-&gt;cur_BytesRead = 0;
	dr-&gt;cur_Writes = 0;
	dr-&gt;cur_BytesWritten = 0;
	dr-&gt;cur_LatentReadTime = 0;
	dr-&gt;cur_LatentWriteTime = 0;
	dr-&gt;cur_ReadErrors = 0;
	dr-&gt;cur_WriteErrors = 0;
	dr-&gt;cur_ReadRetries = 0;
	dr-&gt;cur_WriteRetries = 0;
	dr-&gt;cur_TotalReadTime = 0;
	dr-&gt;cur_TotalWriteTime=0;
    }

    <span class="enscript-comment">/* By this point, we have read in a complete set of diskstats from the sadc
     * data collector.
     * The order of the drives in not guaranteed.
     * The global report structure is a linked list, but may need initialization
     * We need to traverse this list  and transfer the current
     * read data.  If a disk entry isn't found, then we need to allocate one
     * initilize it.
    */</span>
    <span class="enscript-keyword">for</span> (i=0; i&lt; datacount; i++)
    {
	<span class="enscript-type">struct</span> drivestats_report *dr_last = NULL;

	index = databuf[i].drivepath_id;   <span class="enscript-comment">/* use this as index into dp_table */</span>
	
	<span class="enscript-comment">/* find disk entry or allocate new one*/</span>
	<span class="enscript-keyword">for</span>(dr = dr_head; dr; dr=(<span class="enscript-type">struct</span> drivestats_report *)dr-&gt;next)
	{
	    dr_last = dr;
	    <span class="enscript-keyword">if</span>(index == dr-&gt;drivepath_id)
		<span class="enscript-keyword">break</span>;
	} 
	
	<span class="enscript-keyword">if</span> (dr == NULL)
	{
	    <span class="enscript-comment">/* allocate new entry */</span>
	    <span class="enscript-keyword">if</span>((dr = (<span class="enscript-type">struct</span> drivestats_report *)malloc(<span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> drivestats_report))) == NULL)
	    {
		fprintf(stderr, <span class="enscript-string">&quot;sar: malloc error\n&quot;</span>);
		exit(EXIT_FAILURE);
	    }
	    bzero((<span class="enscript-type">char</span> *)dr, <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> drivestats_report));
	    dr-&gt;blocksize = databuf[i].blocksize;
	    dr-&gt;drivepath_id = index;
	    dr-&gt;next = NULL;
	    dr-&gt;avg_count = 0;

	    <span class="enscript-comment">/* get the BSDName which should be in the table by now */</span>
	    <span class="enscript-keyword">if</span> ((index &lt; dp_count) &amp;&amp; (dp_table[index].state != DPSTATE_UNINITIALIZED))
		strncpy(dr-&gt;name, dp_table[index].BSDName, MAXDRIVENAME+1);
	    <span class="enscript-keyword">else</span>
		strcpy(dr-&gt;name, <span class="enscript-string">&quot;disk??&quot;</span>);

	    <span class="enscript-keyword">if</span> (dr_head == NULL)
	    {
		dr_head = dr;
		dr_head-&gt;next = NULL;
	    }
	    <span class="enscript-keyword">else</span>
	    {
		dr_last-&gt;next = (<span class="enscript-type">char</span> *)dr;
	    }
	} <span class="enscript-comment">/* end if dr == NULL */</span>
	
	dr-&gt;present = TRUE;
	dr-&gt;cur_Reads = databuf[i].Reads;
	dr-&gt;cur_BytesRead = databuf[i].BytesRead;
	dr-&gt;cur_Writes = databuf[i].Writes;
	dr-&gt;cur_BytesWritten = databuf[i].BytesWritten;
	dr-&gt;cur_LatentReadTime = databuf[i].LatentReadTime;
	dr-&gt;cur_LatentWriteTime = databuf[i].LatentWriteTime;
	dr-&gt;cur_ReadErrors = databuf[i].ReadErrors;
	dr-&gt;cur_WriteErrors = databuf[i].WriteErrors;
	dr-&gt;cur_ReadRetries = databuf[i].ReadRetries;
	dr-&gt;cur_WriteRetries = databuf[i].WriteRetries;
	dr-&gt;cur_TotalReadTime = databuf[i].TotalReadTime;
	dr-&gt;cur_TotalWriteTime=databuf[i].TotalWriteTime;
    } <span class="enscript-comment">/* end for loop */</span>
	
    <span class="enscript-comment">/* Reinitialize the prev and avg fields when
     * This is a new disk
     * This is a changed disk - name change implies disk swapping
     * This disk is not present in this sample
     */</span>
    <span class="enscript-keyword">for</span>(dr = dr_head; dr; dr=(<span class="enscript-type">struct</span> drivestats_report *)dr-&gt;next)
    {
	<span class="enscript-keyword">if</span> (dr-&gt;drivepath_id &gt;= dp_count)
	{
	    <span class="enscript-comment">/* something is amiss */</span>
	    <span class="enscript-keyword">continue</span>;
	}
	<span class="enscript-keyword">else</span>
	{
	    index = dr-&gt;drivepath_id;   <span class="enscript-comment">/* use this as index into dp_table */</span>
	}
	
	<span class="enscript-keyword">if</span> ((flag == INIT_SET) ||
	  (dp_table[index].state == DPSTATE_NEW) ||
	  (dp_table[index].state == DPSTATE_CHANGED) ||
	  (!dr-&gt;present))
	{
	    <span class="enscript-comment">/*
	     * prev will be set to cur
	     * activate the state in dp_table
	     */</span>
	    <span class="enscript-keyword">if</span> (dr-&gt;present)
		dp_table[index].state = DPSTATE_ACTIVE;
	    
	    init_drivestats(dr);
	}
    }
    <span class="enscript-keyword">return</span>(1);
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">init_drivestats</span>(<span class="enscript-type">struct</span> drivestats_report *dr)
{
    dr-&gt;avg_count = 0;
    dr-&gt;prev_Reads = dr-&gt;cur_Reads;
    dr-&gt;avg_Reads = 0;
    dr-&gt;prev_BytesRead = dr-&gt;cur_BytesRead;
    dr-&gt;avg_BytesRead = 0;
    dr-&gt;prev_Writes = dr-&gt;cur_Writes;
    dr-&gt;avg_Writes = 0;
    dr-&gt;prev_BytesWritten = dr-&gt;cur_BytesWritten;
    dr-&gt;avg_BytesWritten = 0;
    dr-&gt;prev_LatentReadTime = dr-&gt;cur_LatentReadTime;
    dr-&gt;avg_LatentReadTime = 0;
    dr-&gt;prev_LatentWriteTime = dr-&gt;cur_LatentWriteTime ;
    dr-&gt;avg_LatentWriteTime = 0;
    dr-&gt;prev_ReadErrors = dr-&gt;cur_ReadErrors ;
    dr-&gt;avg_ReadErrors = 0;
    dr-&gt;prev_WriteErrors = dr-&gt;cur_WriteErrors ;
    dr-&gt;avg_WriteErrors = 0;
    dr-&gt;prev_ReadRetries = dr-&gt;cur_ReadRetries ;
    dr-&gt;avg_ReadRetries = 0;
    dr-&gt;prev_WriteRetries = dr-&gt;cur_WriteRetries ;
    dr-&gt;avg_WriteRetries = 0;
    dr-&gt;prev_TotalReadTime = dr-&gt;cur_TotalReadTime ;
    dr-&gt;avg_TotalReadTime = 0;
    dr-&gt;prev_TotalWriteTime = dr-&gt;cur_TotalWriteTime ;
    dr-&gt;avg_TotalWriteTime = 0;    
}


<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">print_drivestats_sample</span>(<span class="enscript-type">char</span> *timebufptr)
{
    <span class="enscript-type">struct</span> drivestats_report *dr;
    <span class="enscript-type">long</span> <span class="enscript-type">double</span> transfers_per_second;
    <span class="enscript-type">long</span> <span class="enscript-type">double</span> kb_per_transfer, mb_per_second;
    u_int64_t interval_bytes, interval_transfers, interval_blocks;
    u_int64_t interval_time;
    <span class="enscript-type">long</span> <span class="enscript-type">double</span> blocks_per_second, ms_per_transaction;

    <span class="enscript-keyword">if</span> (flag_count &gt; 1)
	print_column_heading(SAR_DRIVESTATS, timebufptr, 0);
	
    <span class="enscript-keyword">for</span> (dr=dr_head; dr; dr=(<span class="enscript-type">struct</span> drivestats_report *)dr-&gt;next)
    {
	<span class="enscript-keyword">if</span>(!dr-&gt;present)
	    <span class="enscript-keyword">continue</span>;

	<span class="enscript-comment">/*
	 * This sanity check is for drives that get removed and then
	 * returned during the sampling sleep interval.  If anything
	 * looks out of sync, reinit and skip this entry.  There is
	 * no way to guard against this entirely.
	 */</span>
	<span class="enscript-keyword">if</span> ((dr-&gt;cur_Reads &lt; dr-&gt;prev_Reads) ||
	  (dr-&gt;cur_BytesRead &lt; dr-&gt;prev_BytesRead) ||
	  (dr-&gt;cur_Writes &lt; dr-&gt;prev_Writes) ||
	  (dr-&gt;cur_BytesWritten &lt; dr-&gt;prev_BytesWritten))
	{
	    init_drivestats(dr);
	    <span class="enscript-keyword">continue</span>;
	}

	dr-&gt;avg_count++;

	dr-&gt;cur_Reads -= dr-&gt;prev_Reads;
	dr-&gt;prev_Reads += dr-&gt;cur_Reads;
	dr-&gt;avg_Reads += dr-&gt;cur_Reads;
	  
        dr-&gt;cur_BytesRead -= dr-&gt;prev_BytesRead;
	dr-&gt;prev_BytesRead += dr-&gt;cur_BytesRead;
	dr-&gt;avg_BytesRead += dr-&gt;cur_BytesRead;
	
	dr-&gt;cur_Writes -= dr-&gt;prev_Writes ;
	dr-&gt;prev_Writes += dr-&gt;cur_Writes ;
	dr-&gt;avg_Writes += dr-&gt;cur_Writes ;

	dr-&gt;cur_BytesWritten -= dr-&gt;prev_BytesWritten ;
	dr-&gt;prev_BytesWritten += dr-&gt;cur_BytesWritten ;
	dr-&gt;avg_BytesWritten += dr-&gt;cur_BytesWritten ;

	dr-&gt;cur_LatentReadTime -= dr-&gt;prev_LatentReadTime ;
	dr-&gt;prev_LatentReadTime += dr-&gt;cur_LatentReadTime ;
	dr-&gt;avg_LatentReadTime += dr-&gt;cur_LatentReadTime ;

	dr-&gt;cur_LatentWriteTime -= dr-&gt;prev_LatentWriteTime ;
	dr-&gt;prev_LatentWriteTime += dr-&gt;cur_LatentWriteTime ;
	dr-&gt;avg_LatentWriteTime += dr-&gt;cur_LatentWriteTime ;	

	dr-&gt;cur_ReadErrors -= dr-&gt;prev_ReadErrors ;
	dr-&gt;prev_ReadErrors += dr-&gt;cur_ReadErrors ;
	dr-&gt;avg_ReadErrors += dr-&gt;cur_ReadErrors ;

	dr-&gt;cur_WriteErrors -= dr-&gt;prev_WriteErrors ;
	dr-&gt;prev_WriteErrors += dr-&gt;cur_WriteErrors ;
	dr-&gt;avg_WriteErrors += dr-&gt;cur_WriteErrors ;

	dr-&gt;cur_ReadRetries -= dr-&gt;prev_ReadRetries ;
	dr-&gt;prev_ReadRetries += dr-&gt;cur_ReadRetries ;
	dr-&gt;avg_ReadRetries += dr-&gt;cur_ReadRetries ;

	dr-&gt;cur_WriteRetries -= dr-&gt;prev_WriteRetries ;
	dr-&gt;prev_WriteRetries += dr-&gt;cur_WriteRetries;
	dr-&gt;avg_WriteRetries += dr-&gt;cur_WriteRetries;

	dr-&gt;cur_TotalReadTime -= dr-&gt;prev_TotalReadTime ;
	dr-&gt;prev_TotalReadTime += dr-&gt;cur_TotalReadTime ;
	dr-&gt;avg_TotalReadTime += dr-&gt;cur_TotalReadTime ;

	dr-&gt;cur_TotalWriteTime -= dr-&gt;prev_TotalWriteTime ;
	dr-&gt;prev_TotalWriteTime += dr-&gt;cur_TotalWriteTime ;
	dr-&gt;avg_TotalWriteTime += dr-&gt;cur_TotalWriteTime ;

	<span class="enscript-comment">/* I/O volume */</span>
	interval_bytes = dr-&gt;cur_BytesRead + dr-&gt;cur_BytesWritten;

	<span class="enscript-comment">/* I/O counts */</span>
	interval_transfers = dr-&gt;cur_Reads + dr-&gt;cur_Writes;

	<span class="enscript-comment">/* I/O time */</span>
	interval_time = dr-&gt;cur_LatentReadTime + dr-&gt;cur_LatentWriteTime;

	interval_blocks = interval_bytes / dr-&gt;blocksize;
	blocks_per_second = interval_blocks / avg_interval;
	transfers_per_second = interval_transfers / avg_interval;
	mb_per_second = (interval_bytes / avg_interval) / (1024 *1024);

	kb_per_transfer = (interval_transfers &gt; 0) ?
	  ((<span class="enscript-type">long</span> <span class="enscript-type">double</span>)interval_bytes / interval_transfers)
	  / 1024 : 0;

	<span class="enscript-comment">/* times are in nanoseconds, convert to milliseconds */</span>
	ms_per_transaction = (interval_transfers &gt; 0) ?
	  ((<span class="enscript-type">long</span> <span class="enscript-type">double</span>)interval_time / interval_transfers)
	  / 1000 : 0;

	<span class="enscript-comment">/* print device name */</span>
	fprintf(stdout, <span class="enscript-string">&quot;%s   %-10s&quot;</span>, timebufptr, dr-&gt;name);
	  
	<span class="enscript-comment">/* print transfers per second */</span>
	fprintf(stdout, <span class="enscript-string">&quot;%4.0Lf       &quot;</span>, transfers_per_second);
	
	<span class="enscript-comment">/* print blocks per second - in device blocksize */</span>
	fprintf(stdout, <span class="enscript-string">&quot;%4.0Lf\n&quot;</span>, blocks_per_second);
    }
}

<span class="enscript-comment">/*
 * Print averages before exiting.
 */</span>
<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">exit_average</span>()
{
    <span class="enscript-type">int</span> i;
    
    <span class="enscript-keyword">if</span> (avg_counter &lt;= 0 )
	exit(0);

    <span class="enscript-keyword">if</span> (oflag)
      {
	<span class="enscript-keyword">if</span> (ofd)
	  close (ofd);
	ofd = 0;
      }

    <span class="enscript-keyword">if</span> (uflag) <span class="enscript-comment">/* print cpu averages */</span>
    {
	<span class="enscript-keyword">if</span>(flag_count &gt; 1)
	    print_column_heading(SAR_CPU, 0, 0);
    
        fprintf(stdout, <span class="enscript-string">&quot;Average:  %5d   &quot;</span>,
	   (<span class="enscript-type">int</span>)avg_cpuload.cpu_ticks[CPU_STATE_USER]
	  / (avg_counter ? avg_counter : 1));

	fprintf(stdout, <span class="enscript-string">&quot;%4d   &quot;</span>, 
	   (<span class="enscript-type">int</span>)avg_cpuload.cpu_ticks[CPU_STATE_NICE]
	  / (avg_counter ? avg_counter : 1));

	fprintf(stdout, <span class="enscript-string">&quot;%4d   &quot;</span>, 
	   (<span class="enscript-type">int</span>)avg_cpuload.cpu_ticks[CPU_STATE_SYSTEM]
	  / (avg_counter ? avg_counter : 1));

	fprintf(stdout, <span class="enscript-string">&quot;%4d   \n&quot;</span>,
	   (<span class="enscript-type">int</span>)avg_cpuload.cpu_ticks[CPU_STATE_IDLE]
	  / (avg_counter ? avg_counter : 1));
	
	fflush(stdout);	
    }    


    <span class="enscript-keyword">if</span> (gflag) <span class="enscript-comment">/* print page-out averages */</span>
    {
	<span class="enscript-keyword">if</span> (flag_count &gt; 1)
	    print_column_heading(SAR_VMSTAT, 0, 0);
	
	fprintf(stdout, <span class="enscript-string">&quot;Average:   %8.1f\n&quot;</span>,
	(<span class="enscript-type">float</span>)((avg_vmstat.pageouts / (avg_counter ? avg_counter : 1)) / avg_interval));
	fflush(stdout);	
    }

    <span class="enscript-keyword">if</span> (pflag) <span class="enscript-comment">/* print page-in averages */</span>
    {
	<span class="enscript-keyword">if</span> (flag_count &gt; 1)
	    print_column_heading(SAR_VMSTAT, 0, 1);	    
	
	fprintf(stdout, <span class="enscript-string">&quot;Average:   %8.1f      %8.1f      %8.1f\n&quot;</span>,
	  (<span class="enscript-type">float</span>)(((<span class="enscript-type">float</span>)avg_vmstat.pageins / (avg_counter ? avg_counter : 1)) / avg_interval),
	  (<span class="enscript-type">float</span>)(((<span class="enscript-type">float</span>)avg_vmstat.cow_faults / (avg_counter ? avg_counter : 1)) / avg_interval),
	  (<span class="enscript-type">float</span>)(((<span class="enscript-type">float</span>)avg_vmstat.faults / (avg_counter ? avg_counter : 1)) / avg_interval));
	fflush(stdout);
    }

    <span class="enscript-keyword">if</span> (dflag) <span class="enscript-comment">/* print drivestats averages */</span>
    {
	<span class="enscript-type">struct</span> drivestats_report *dr;
	<span class="enscript-type">long</span> <span class="enscript-type">double</span> transfers_per_second;
	<span class="enscript-type">long</span> <span class="enscript-type">double</span> kb_per_transfer, mb_per_second;
	u_int64_t total_bytes, total_transfers, total_blocks;
	u_int64_t total_time;
	<span class="enscript-type">long</span> <span class="enscript-type">double</span> blocks_per_second, ms_per_transaction;
	<span class="enscript-type">int</span> msdig;

	<span class="enscript-keyword">if</span> (flag_count &gt; 1)
	    print_column_heading(SAR_DRIVESTATS, 0, 0);

	<span class="enscript-keyword">for</span> (dr=dr_head; dr; dr=(<span class="enscript-type">struct</span> drivestats_report *)dr-&gt;next)
	{
	    <span class="enscript-comment">/* don't bother to print out averages for disks that were removed */</span>
	    <span class="enscript-keyword">if</span> (!dr-&gt;present)
		<span class="enscript-keyword">continue</span>;

	    fprintf(stdout, <span class="enscript-string">&quot;           %s    %s\n&quot;</span>,
	      dp_table[dr-&gt;drivepath_id].BSDName, dp_table[dr-&gt;drivepath_id].ioreg_path);	    
	    
	    <span class="enscript-comment">/* I/O volume */</span>
	    total_bytes = dr-&gt;avg_BytesRead + dr-&gt;avg_BytesWritten;

	    <span class="enscript-comment">/* I/O counts */</span>
	    total_transfers = dr-&gt;avg_Reads + dr-&gt;avg_Writes;

	    <span class="enscript-comment">/* I/O time */</span>
	    total_time = dr-&gt;avg_LatentReadTime + dr-&gt;avg_LatentWriteTime;

	    total_blocks = total_bytes / dr-&gt;blocksize;
	    blocks_per_second = total_blocks / avg_interval;
	    transfers_per_second = total_transfers / avg_interval;
	    mb_per_second = (total_bytes / avg_interval) / (1024 *1024);

	    kb_per_transfer = (total_transfers &gt; 0) ?
	      ((<span class="enscript-type">long</span> <span class="enscript-type">double</span>)total_bytes / total_transfers)
	      / 1024 : 0;

	    <span class="enscript-comment">/* times are in nanoseconds, convert to milliseconds */</span>
	    ms_per_transaction = (total_transfers &gt; 0) ?
	      ((<span class="enscript-type">long</span> <span class="enscript-type">double</span>)total_time / total_transfers)
	      / 1000 : 0;
	    msdig = (ms_per_transaction &lt; 100.0) ? 1 : 0;
	    fprintf(stdout, <span class="enscript-string">&quot;Average:   %-10s %4.0Lf      %4.0Lf\n&quot;</span>,
	      dr-&gt;name,
	      (transfers_per_second / dr-&gt;avg_count),
	      (blocks_per_second / dr-&gt;avg_count));
	    
	    fflush(stdout);	
	}
    } <span class="enscript-comment">/* end if dflag */</span>

    <span class="enscript-keyword">if</span> (nflag)
    {
	<span class="enscript-type">int</span> avg_count;
	
	<span class="enscript-keyword">if</span> (network_mode &amp; NET_DEV_MODE)	    
	{
	    <span class="enscript-keyword">if</span> (flag_count &gt; 1)
		print_column_heading(SAR_NETSTATS, 0, NET_DEV_MODE);
	    <span class="enscript-keyword">for</span> (i = 0; i &lt; nr_count; i++)
	    {
		<span class="enscript-keyword">if</span> (!nr_table[i].valid)
		    <span class="enscript-keyword">continue</span>;

		<span class="enscript-keyword">if</span>(nr_table[i].avg_count == 0)
		    avg_count = 1;
		<span class="enscript-keyword">else</span>
		    avg_count = nr_table[i].avg_count;

		fprintf(stdout, <span class="enscript-string">&quot;Average:   %-8.8s&quot;</span>, nr_table[i].tname_unit);
	    
		fprintf (stdout, <span class="enscript-string">&quot;%8llu    &quot;</span>,
		  ((nr_table[i].avg_ipackets / avg_count) / avg_interval));

		fprintf (stdout, <span class="enscript-string">&quot;%10llu    &quot;</span>,
		  ((nr_table[i].avg_ibytes / avg_count) / avg_interval));

		fprintf (stdout, <span class="enscript-string">&quot;%8llu    &quot;</span>,
		  ((nr_table[i].avg_opackets / avg_count) / avg_interval));
		
		fprintf (stdout, <span class="enscript-string">&quot;%10llu\n&quot;</span>,
		  ((nr_table[i].avg_obytes / avg_count) / avg_interval));
		
		fflush(stdout);
	    }
	}

	<span class="enscript-keyword">if</span> (network_mode &amp; NET_EDEV_MODE)	    
	{

	    <span class="enscript-keyword">if</span>(flag_count &gt; 1)
		print_column_heading(SAR_NETSTATS, 0, NET_EDEV_MODE);

	    <span class="enscript-keyword">for</span> (i = 0; i &lt; nr_count; i++)
	    {
		<span class="enscript-keyword">if</span> (!nr_table[i].valid)
		    <span class="enscript-keyword">continue</span>;

		<span class="enscript-keyword">if</span>(nr_table[i].avg_count == 0)
		    avg_count = 1;
		<span class="enscript-keyword">else</span>
		    avg_count = nr_table[i].avg_count;

		fprintf(stdout, <span class="enscript-string">&quot;Average:   %-8.8s  &quot;</span>, nr_table[i].tname_unit);
	    
		fprintf (stdout, <span class="enscript-string">&quot;%7llu    &quot;</span>,		  
		  ((nr_table[i].avg_ierrors / avg_count) / avg_interval));
		
		fprintf (stdout, <span class="enscript-string">&quot;%7llu    &quot;</span>,
		  ((nr_table[i].avg_oerrors / avg_count) / avg_interval));

		fprintf (stdout, <span class="enscript-string">&quot;%5llu    &quot;</span>,
		  ((nr_table[i].avg_collisions / avg_count) / avg_interval));

		fprintf (stdout, <span class="enscript-string">&quot;   %5llu\n&quot;</span>,
		  ((nr_table[i].avg_drops / avg_count) / avg_interval));
		
		fflush(stdout);
	    }
	}	

    } <span class="enscript-comment">/* end if nflag */</span>
    exit(0);
}


<span class="enscript-comment">/*
 * Return &lt; 0 failure, debugging purposes only
 * Return = 0 data skipped
 * Return &gt; 0 success
 */</span>
  
<span class="enscript-type">static</span> <span class="enscript-type">int</span>
<span class="enscript-function-name">get_drivepath_sample</span>(flag, hdr)
    <span class="enscript-type">int</span> flag;
    <span class="enscript-type">struct</span> record_hdr *hdr;
{
    size_t datasize;
    <span class="enscript-type">struct</span> drivepath dp;
    <span class="enscript-type">struct</span> drivestats_report *dr;
    <span class="enscript-type">int</span> i, n;

    datasize = hdr-&gt;rec_count * hdr-&gt;rec_size;

    <span class="enscript-keyword">if</span> (datasize != <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> drivepath))
    {
	<span class="enscript-comment">/* read past the data but don't do anything with it */</span>
	skip_data(datasize);
	<span class="enscript-keyword">return</span>(0);
    }

    read_record_data ((<span class="enscript-type">char</span> *)&amp;dp, (<span class="enscript-type">int</span>)<span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> drivepath), TRUE );

    <span class="enscript-comment">/*
     * If state is new -- put a new entry in the dp_table.
     * If state is changed -- traverse the drivestats_report table
     * and copy new name.
     */</span>
    <span class="enscript-keyword">if</span> (dp.state == DPSTATE_NEW)
    {

	<span class="enscript-keyword">if</span> (dp_table == NULL)
	{
	    <span class="enscript-keyword">if</span> (dp.drivepath_id != 0)
		<span class="enscript-keyword">return</span>(-1);
	    <span class="enscript-comment">/* First setup of internal drivepath table */</span>
	    dp_table = (<span class="enscript-type">struct</span> drivepath *)malloc(<span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> drivepath));
	    <span class="enscript-keyword">if</span> (dp_table == NULL)
		<span class="enscript-keyword">return</span>(-2);
	    dp_count = 1;
	}

	<span class="enscript-keyword">if</span> (dflag)
	    fprintf(stdout, <span class="enscript-string">&quot;New Disk: [%s] %s\n&quot;</span>, dp.BSDName, dp.ioreg_path);

	<span class="enscript-comment">/* traverse table and find next uninitialized entry */</span>
	<span class="enscript-keyword">for</span> (i = 0; i&lt; dp_count; i++)
	{
	    <span class="enscript-keyword">if</span> (dp_table[i].state == DPSTATE_UNINITIALIZED)
	    {
		<span class="enscript-keyword">if</span> (dp.drivepath_id != i)
		{
		    <span class="enscript-comment">/* the table is out of sync - this should not happen */</span>
		    <span class="enscript-keyword">return</span> (-3);
		}
		dp_table[i] = dp;
		<span class="enscript-keyword">return</span>(1);
	    }
	}
	<span class="enscript-comment">/*
	 * If we get here, we've run out of table entries.
	 * Double the size of the table, then assign the next entry.
	 */</span>
	<span class="enscript-keyword">if</span> (dp.drivepath_id != i)
	{
	    <span class="enscript-comment">/* the table is out of sync - this should not happen */</span>
	    <span class="enscript-keyword">return</span> (-4);
	}
	n = dp_count * 2;
	dp_table = (<span class="enscript-type">struct</span> drivepath *)realloc(dp_table, n * <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> drivepath));
	bzero(&amp;dp_table[dp_count], dp_count * <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> drivepath));
	dp_table[dp_count] = dp;
	dp_count = n;
	<span class="enscript-keyword">return</span>(1);

    }
    <span class="enscript-keyword">else</span> <span class="enscript-keyword">if</span> (dp.state == DPSTATE_CHANGED)
    {

	  <span class="enscript-comment">/* Update the name in the table */</span>
	<span class="enscript-keyword">if</span> ((dp.drivepath_id &lt; dp_count) &amp;&amp; (dp_table[dp.drivepath_id].state != DPSTATE_UNINITIALIZED))
	{
	    <span class="enscript-keyword">if</span> (strcmp(dp_table[dp.drivepath_id].ioreg_path, dp.ioreg_path) != 0)
	    {
		<span class="enscript-comment">/* something is amiss */</span>
		<span class="enscript-keyword">return</span> (-5);
	    }
	    <span class="enscript-keyword">else</span>
	    {
		<span class="enscript-keyword">if</span> (dflag)
		{
		    fprintf(stdout, <span class="enscript-string">&quot;Change: [%s] %s\n&quot;</span>, dp.BSDName,
		      dp_table[dp.drivepath_id].ioreg_path);
		}
		strcpy(dp_table[dp.drivepath_id].BSDName, dp.BSDName);

		<span class="enscript-keyword">for</span>(dr = dr_head; dr; dr=(<span class="enscript-type">struct</span> drivestats_report *)dr-&gt;next)
		  {
		    <span class="enscript-keyword">if</span> (dr-&gt;drivepath_id == dp.drivepath_id)
		      strcpy(dr-&gt;name, dp.BSDName);
		  }
		<span class="enscript-keyword">return</span>(1);
	    }
	}
	<span class="enscript-keyword">else</span>
	    <span class="enscript-keyword">return</span>(-6);
    }
    <span class="enscript-keyword">return</span>(-7);
}

<span class="enscript-comment">/*
 * Bytes and packet counts are used to track
 * counter wraps.  So, don't enforce the
 * NET_DEV_MODE or NET_EDEV_MODE  in here.
 * Maintain all the stats.
 */</span>
<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">set_cur_netstats</span>(<span class="enscript-type">struct</span> netstats_report *nr, <span class="enscript-type">struct</span> netstats *ns)
{

    nr-&gt;cur_ipackets   = ns-&gt;net_ipackets;
    nr-&gt;cur_ibytes     = ns-&gt;net_ibytes;
    nr-&gt;cur_opackets   = ns-&gt;net_opackets;
    nr-&gt;cur_obytes     = ns-&gt;net_obytes;

    nr-&gt;cur_ierrors    = ns-&gt;net_ierrors;
    nr-&gt;cur_oerrors    = ns-&gt;net_oerrors;
    nr-&gt;cur_collisions = ns-&gt;net_collisions;
    nr-&gt;cur_drops      = ns-&gt;net_drops;

    nr-&gt;cur_imcasts    = ns-&gt;net_imcasts;
    nr-&gt;cur_omcasts    = ns-&gt;net_omcasts;

}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">init_prev_netstats</span>(<span class="enscript-type">struct</span> netstats_report *nr)
{
    nr-&gt;avg_count = 0;
    nr-&gt;valid = 1;
    nr-&gt;present = 1;

    nr-&gt;prev_ipackets = nr-&gt;cur_ipackets;
    nr-&gt;avg_ipackets  = 0;
    nr-&gt;prev_ibytes   = nr-&gt;cur_ibytes;
    nr-&gt;avg_ibytes    = 0;	
    nr-&gt;prev_opackets = nr-&gt;cur_opackets;
    nr-&gt;avg_opackets  = 0;
    nr-&gt;prev_obytes   = nr-&gt;cur_obytes;
    nr-&gt;avg_obytes    = 0;

    nr-&gt;prev_ierrors  = nr-&gt;cur_ierrors;
    nr-&gt;avg_ierrors   = 0;
    nr-&gt;prev_oerrors  = nr-&gt;cur_oerrors ;
    nr-&gt;avg_oerrors   = 0;
    nr-&gt;prev_collisions = nr-&gt;cur_collisions ;
    nr-&gt;avg_collisions  = 0;
    nr-&gt;prev_drops  = nr-&gt;cur_drops ;
    nr-&gt;avg_drops   = 0;

    <span class="enscript-comment">/* track these, but never displayed */</span>    
    nr-&gt;prev_imcasts  = nr-&gt;cur_imcasts;
    nr-&gt;avg_imcasts = 0;
    nr-&gt;prev_omcasts  = nr-&gt;cur_omcasts;
    nr-&gt;avg_omcasts = 0;    
}

<span class="enscript-comment">/*
 * Success : 1
 * Failure : 0
 */</span>
<span class="enscript-type">static</span> <span class="enscript-type">int</span>
<span class="enscript-function-name">get_netstats_sample</span>(flag, hdr)
    <span class="enscript-type">int</span> flag;
    <span class="enscript-type">struct</span> record_hdr *hdr;
{
    <span class="enscript-type">struct</span> netstats *databuf = NULL;
    size_t datasize;
    <span class="enscript-type">int</span>    datacount;
    <span class="enscript-type">int</span>    i, j;

    datasize = hdr-&gt;rec_count * hdr-&gt;rec_size;
    datacount = hdr-&gt;rec_count;

    <span class="enscript-keyword">if</span> (hdr-&gt;rec_size != <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> netstats))
    {
	<span class="enscript-comment">/* something isn't right... read past the data but don't analyze it */</span>
	skip_data(datasize);
	<span class="enscript-keyword">return</span>(0);
    }

    <span class="enscript-comment">/* malloc new or bigger read buffer */</span>
    <span class="enscript-keyword">if</span>((netstat_readbuf == NULL) || (netstat_readbuf_size &lt; datasize))
    {
	<span class="enscript-keyword">if</span> (netstat_readbuf)
	    free (netstat_readbuf);
	
	<span class="enscript-keyword">if</span> ((netstat_readbuf = (<span class="enscript-type">struct</span> netstats *)malloc(datasize)) == NULL)
	{
	    fprintf(stderr, <span class="enscript-string">&quot;sar: malloc failed\n&quot;</span>);
	    exit (EXIT_FAILURE);
	}
	netstat_readbuf_size = datasize;
    }

    bzero(netstat_readbuf, netstat_readbuf_size);
    databuf = netstat_readbuf;

    read_record_data ((<span class="enscript-type">char</span> *)databuf, datasize, TRUE );    

    <span class="enscript-keyword">if</span> (nr_table == NULL)
    {
	<span class="enscript-comment">/* initial internal table setup */</span>
	nr_table = (<span class="enscript-type">struct</span> netstats_report *)malloc(datacount * <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> netstats_report));
	nr_count = datacount;
	bzero(nr_table, (datacount * <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> netstats_report)));

	<span class="enscript-comment">/* on first init, this is faster than finding our way to NEW_ENTRY */</span>
	<span class="enscript-keyword">for</span> (i = 0; i &lt; datacount; i++)
	{
	    <span class="enscript-keyword">if</span> (!(network_mode &amp; NET_PPP_MODE))
	    {
		<span class="enscript-keyword">if</span> (!strncmp(databuf[i].tname_unit, <span class="enscript-string">&quot;ppp&quot;</span>, 3))
		    <span class="enscript-keyword">continue</span>;   <span class="enscript-comment">/*
				 * Skip ppp interfaces.
				 * ie don't even put them in this internal table.
				 */</span>
	    }
	    strncpy(nr_table[i].tname_unit, databuf[i].tname_unit, MAX_TNAME_UNIT_SIZE);
	    nr_table[i].tname_unit[MAX_TNAME_UNIT_SIZE] = <span class="enscript-string">'\0'</span>;
	    set_cur_netstats(&amp;nr_table[i], &amp;databuf[i]);
	    init_prev_netstats(&amp;nr_table[i]);
	}
	<span class="enscript-keyword">return</span>(1);
    }

    <span class="enscript-comment">/*
     * clear all the present flags.
     * As we traverse the current sample set
     * and update the internal table, the flag
     * is reset.
     */</span>
    <span class="enscript-keyword">for</span> (i = 0; i &lt; nr_count; i++)
    {
	nr_table[i].present = 0;
    }

    <span class="enscript-comment">/*
     * Find and update table entries.
     * Init new entries.
     */</span>
    <span class="enscript-keyword">for</span> (i=0; i&lt;datacount; i++)
    {
	<span class="enscript-type">int</span> found;
	<span class="enscript-type">char</span> *name;
	<span class="enscript-type">int</span> nr_index;
	<span class="enscript-type">int</span> n;

	name = databuf[i].tname_unit;
	found = 0;

	<span class="enscript-keyword">if</span> (!(network_mode &amp; NET_PPP_MODE))
	{
	    <span class="enscript-keyword">if</span> (!strncmp(name, <span class="enscript-string">&quot;ppp&quot;</span>, 3))
		<span class="enscript-keyword">continue</span>;   <span class="enscript-comment">/* skip ppp interfaces */</span>
	}

	<span class="enscript-comment">/* Find the matching entry using the interface name */</span>
	<span class="enscript-keyword">for</span> (j=0; j &lt; nr_count &amp;&amp; !found; j++)
	{
	    <span class="enscript-keyword">if</span> (nr_table[j].valid)
	    {
		<span class="enscript-keyword">if</span>(!strcmp(nr_table[j].tname_unit, name))
		{
		    found = 1;
		    nr_table[j].present = 1;
		    set_cur_netstats(&amp;nr_table[j], &amp;databuf[i]);
		}
	    }
	} <span class="enscript-comment">/* end for */</span>

	<span class="enscript-keyword">if</span> (!found)  <span class="enscript-comment">/* this is a new entry */</span>
	{
	    <span class="enscript-comment">/* Find an invalid entry in the table and init it */</span>
	    <span class="enscript-keyword">for</span> (j=0; j &lt; nr_count; j++)
	    {
		<span class="enscript-keyword">if</span> (!nr_table[j].valid)
		{
		    nr_index = j;
		    <span class="enscript-keyword">goto</span> <span class="enscript-reference">NEW_ENTRY</span>;
		}
	    }

	    <span class="enscript-comment">/* we ran out of entries... grow the table */</span>
	    n = nr_count * 2;
	    nr_table = (<span class="enscript-type">struct</span> netstats_report *)realloc(nr_table, n * <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> netstats_report));
	    bzero(&amp;nr_table[nr_count], nr_count * <span class="enscript-keyword">sizeof</span> (<span class="enscript-type">struct</span> netstats_report));
	    nr_index = nr_count;
	    nr_count = n;
	    
	    <span class="enscript-reference">NEW_ENTRY</span>:
	    strncpy(nr_table[nr_index].tname_unit, databuf[i].tname_unit, MAX_TNAME_UNIT_SIZE);
	    nr_table[nr_index].tname_unit[MAX_TNAME_UNIT_SIZE] = <span class="enscript-string">'\0'</span>;
	    set_cur_netstats(&amp;nr_table[nr_index], &amp;databuf[i]);
	    init_prev_netstats(&amp;nr_table[nr_index]);
	}
	
    } <span class="enscript-comment">/* end for */</span>

    <span class="enscript-comment">/*
     * Traverse the internal table.  Any valid entry that wasn't
     * present in this sample is cleared for reuse.
     */</span>
    <span class="enscript-keyword">for</span> (i = 0; i &lt; nr_count; i++)
    {
	<span class="enscript-keyword">if</span> (nr_table[i].valid)
	{
	    <span class="enscript-keyword">if</span> (nr_table[i].present == 0)
		bzero(&amp;nr_table[i], <span class="enscript-keyword">sizeof</span>(<span class="enscript-type">struct</span> netstats_report));
	}
    }
    <span class="enscript-keyword">return</span> (1);
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">print_netstats_sample</span>(<span class="enscript-type">char</span> *timebufptr)
{
    <span class="enscript-type">int</span> i;

    <span class="enscript-keyword">for</span> (i=0; i &lt; nr_count; i++)
    {
	<span class="enscript-keyword">if</span> (!nr_table[i].valid)
	    <span class="enscript-keyword">continue</span>;

	<span class="enscript-comment">/*
	 * This is where we attempt to handle counters that
	 * might wrap ... the kernel netstats are only 32 bits.
	 *
	 * Interfaces may go away and then return within the
	 * sampling period.  This can't be detected and it
	 * may look like a counter wrap.  An interface generation
	 * counter will help... but isn't implemented at this time.
	 */</span>

	<span class="enscript-comment">/* 
	 * The ppp interfaces are very likely to come and go during
	 * a sampling period.  During the normal life of a ppp interface,
	 * it's less likely that the packet counter will wrap, so if
	 * it appears to have done so, is probably because the
	 * interface unit number has been reused. 
	 * We reinitialize that interface in that case.
	 */</span>
	<span class="enscript-keyword">if</span> (network_mode &amp; NET_PPP_MODE)
	{
	    <span class="enscript-comment">/*
	     * ppp interfaces won't even make it into this table
	     * when NET_PPP_MODE isn't set
	    */</span>
	    <span class="enscript-keyword">if</span> (!strncmp(nr_table[i].tname_unit, <span class="enscript-string">&quot;ppp&quot;</span>, 3))
	    {
		<span class="enscript-comment">/*
		 * Both ipackets and opackets have to be less
		 * than the previous counter to cause us to reinit.
		 */</span>

		<span class="enscript-keyword">if</span> ((nr_table[i].cur_ipackets &lt; nr_table[i].prev_ipackets)
		  &amp;&amp; (nr_table[i].cur_opackets &lt; nr_table[i].prev_opackets))
		{
		    init_prev_netstats(&amp;nr_table[i]);
		    <span class="enscript-keyword">continue</span>;
		}
	    }
	}

	nr_table[i].avg_count ++;

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span>
	<span class="enscript-keyword">while</span> (nr_table[i].cur_ipackets &lt; nr_table[i].prev_ipackets)
	    nr_table[i].cur_ipackets += 0x100000000LL;
#<span class="enscript-reference">endif</span> <span class="enscript-comment">/* IFNET_32_BIT_COUNTERS */</span>
	nr_table[i].cur_ipackets -= nr_table[i].prev_ipackets;
	nr_table[i].prev_ipackets += nr_table[i].cur_ipackets;
	nr_table[i].avg_ipackets += nr_table[i].cur_ipackets;
	

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span>	
	<span class="enscript-keyword">while</span> (nr_table[i].cur_ibytes &lt; nr_table[i].prev_ibytes)
	    nr_table[i].cur_ibytes += 0x100000000LL;
#<span class="enscript-reference">endif</span> <span class="enscript-comment">/* IFNET_32_BIT_COUNTERS */</span>
	nr_table[i].cur_ibytes -= nr_table[i].prev_ibytes;
	nr_table[i].prev_ibytes += nr_table[i].cur_ibytes;
	nr_table[i].avg_ibytes += nr_table[i].cur_ibytes;


#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span>	
	<span class="enscript-keyword">while</span> (nr_table[i].cur_opackets &lt; nr_table[i].prev_opackets)
	    nr_table[i].cur_opackets += 0x100000000LL;
#<span class="enscript-reference">endif</span> <span class="enscript-comment">/* IFNET_32_BIT_COUNTERS */</span>
	nr_table[i].cur_opackets -= nr_table[i].prev_opackets;
	nr_table[i].prev_opackets += nr_table[i].cur_opackets;
	nr_table[i].avg_opackets += nr_table[i].cur_opackets;

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span>
	<span class="enscript-keyword">while</span> (nr_table[i].cur_obytes &lt; nr_table[i].prev_obytes)
	    nr_table[i].cur_obytes += 0x100000000LL;
#<span class="enscript-reference">endif</span> <span class="enscript-comment">/* IFNET_32_BIT_COUNTERS */</span>
	nr_table[i].cur_obytes -= nr_table[i].prev_obytes;
	nr_table[i].prev_obytes += nr_table[i].cur_obytes;
	nr_table[i].avg_obytes += nr_table[i].cur_obytes;


#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span>
	<span class="enscript-keyword">while</span> (nr_table[i].cur_ierrors &lt; nr_table[i].prev_ierrors)
	    nr_table[i].cur_ierrors += 0x100000000LL;
#<span class="enscript-reference">endif</span> <span class="enscript-comment">/* IFNET_32_BIT_COUNTERS */</span>
	nr_table[i].cur_ierrors -= nr_table[i].prev_ierrors;
	nr_table[i].prev_ierrors += nr_table[i].cur_ierrors;
	nr_table[i].avg_ierrors += nr_table[i].cur_ierrors;

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span>
	<span class="enscript-keyword">while</span> (nr_table[i].cur_oerrors &lt; nr_table[i].prev_oerrors)
	    nr_table[i].cur_oerrors += 0x100000000LL;
#<span class="enscript-reference">endif</span> <span class="enscript-comment">/* IFNET_32_BIT_COUNTERS */</span>
	nr_table[i].cur_oerrors -= nr_table[i].prev_oerrors;
	nr_table[i].prev_oerrors += nr_table[i].cur_oerrors;
	nr_table[i].avg_oerrors += nr_table[i].cur_oerrors;

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span>	
	<span class="enscript-keyword">while</span> (nr_table[i].cur_collisions &lt; nr_table[i].prev_collisions)
	    nr_table[i].cur_collisions += 0x100000000LL;
#<span class="enscript-reference">endif</span> <span class="enscript-comment">/* IFNET_32_BIT_COUNTERS */</span>
	nr_table[i].cur_collisions -= nr_table[i].prev_collisions;
	nr_table[i].prev_collisions += nr_table[i].cur_collisions;
	nr_table[i].avg_collisions += nr_table[i].cur_collisions;

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span>
	<span class="enscript-keyword">while</span> (nr_table[i].cur_drops &lt; nr_table[i].prev_drops)
	    nr_table[i].cur_drops += 0x100000000LL;
#<span class="enscript-reference">endif</span> <span class="enscript-comment">/* IFNET_32_BIT_COUNTERS */</span>
	nr_table[i].cur_drops -= nr_table[i].prev_drops;
	nr_table[i].prev_drops += nr_table[i].cur_drops;
	nr_table[i].avg_drops += nr_table[i].cur_drops;

	
#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span>	
	<span class="enscript-keyword">while</span> (nr_table[i].cur_imcasts &lt; nr_table[i].prev_imcasts)
	    nr_table[i].cur_imcasts += 0x100000000LL;
#<span class="enscript-reference">endif</span> <span class="enscript-comment">/* IFNET_32_BIT_COUNTERS */</span>
	nr_table[i].cur_imcasts -= nr_table[i].prev_imcasts;
	nr_table[i].prev_imcasts += nr_table[i].cur_imcasts;
	nr_table[i].avg_imcasts += nr_table[i].cur_imcasts;

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">IFNET_32_BIT_COUNTERS</span>
	<span class="enscript-keyword">while</span> (nr_table[i].cur_omcasts &lt; nr_table[i].prev_omcasts)
	    nr_table[i].cur_omcasts += 0x100000000LL;
#<span class="enscript-reference">endif</span> <span class="enscript-comment">/* IFNET_32_BIT_COUNTERS */</span>
	nr_table[i].cur_omcasts -= nr_table[i].prev_omcasts;
	nr_table[i].prev_omcasts += nr_table[i].cur_omcasts;
	nr_table[i].avg_omcasts += nr_table[i].cur_omcasts;
    }


    <span class="enscript-keyword">if</span> (!(flag_count &gt; 1))
	fprintf(stdout, <span class="enscript-string">&quot;\n&quot;</span>);
    
    <span class="enscript-keyword">if</span> (network_mode &amp; NET_DEV_MODE)
    {
	<span class="enscript-keyword">if</span> (flag_count &gt; 1)
	    print_column_heading(SAR_NETSTATS, timebufptr, NET_DEV_MODE);
	
	<span class="enscript-keyword">for</span> (i=0; i &lt; nr_count; i++)
	{
	    <span class="enscript-keyword">if</span> (!nr_table[i].valid)
		<span class="enscript-keyword">continue</span>;

	    <span class="enscript-keyword">if</span> (!(network_mode &amp; NET_PPP_MODE))
	    {
		<span class="enscript-keyword">if</span> (!strncmp(nr_table[i].tname_unit, <span class="enscript-string">&quot;ppp&quot;</span>, 3))
		{
		    <span class="enscript-keyword">continue</span>;  <span class="enscript-comment">/* skip any ppp interfaces */</span>
		}
	    }
	
	    <span class="enscript-comment">/* print the interface name */</span>
	    fprintf(stdout, <span class="enscript-string">&quot;%s    %-8.8s&quot;</span>, timebufptr, nr_table[i].tname_unit);

	    fprintf (stdout, <span class="enscript-string">&quot;%8llu    &quot;</span>,
	      (nr_table[i].cur_ipackets / avg_interval));

	    fprintf (stdout, <span class="enscript-string">&quot;%10llu    &quot;</span>,
	      (nr_table[i].cur_ibytes / avg_interval));

	    fprintf (stdout, <span class="enscript-string">&quot;%8llu    &quot;</span>,
	      (nr_table[i].cur_opackets / avg_interval));

	    fprintf (stdout, <span class="enscript-string">&quot;%10llu\n&quot;</span>,
	      (nr_table[i].cur_obytes / avg_interval));
	}
    }

    
    <span class="enscript-keyword">if</span> (network_mode &amp; NET_EDEV_MODE)
    {
	<span class="enscript-keyword">if</span>(flag_count &gt; 1)
	{
	    print_column_heading(SAR_NETSTATS, timebufptr, NET_EDEV_MODE);
	}
    
	<span class="enscript-keyword">for</span> (i=0; i &lt; nr_count; i++)
	{
	    <span class="enscript-keyword">if</span> (!nr_table[i].valid)
		<span class="enscript-keyword">continue</span>;
	    
	    <span class="enscript-keyword">if</span> (!(network_mode &amp; NET_PPP_MODE))
	    {
		<span class="enscript-keyword">if</span> (!strncmp(nr_table[i].tname_unit, <span class="enscript-string">&quot;ppp&quot;</span>, 3))
		{
		    <span class="enscript-keyword">continue</span>;  <span class="enscript-comment">/* skip any ppp interfaces */</span>
		}
	    }	

	    <span class="enscript-comment">/* print the interface name */</span>
	    fprintf(stdout, <span class="enscript-string">&quot;%s    %-8.8s  &quot;</span>, timebufptr, nr_table[i].tname_unit);
	    
	    fprintf (stdout, <span class="enscript-string">&quot;%7llu    &quot;</span>,
	      (nr_table[i].cur_ierrors / avg_interval));
	    
	    fprintf (stdout, <span class="enscript-string">&quot;%7llu    &quot;</span>,
	      (nr_table[i].cur_oerrors / avg_interval));
		
	    fprintf (stdout, <span class="enscript-string">&quot;%5llu    &quot;</span>,
	      (nr_table[i].cur_collisions / avg_interval));
	    
	    fprintf (stdout, <span class="enscript-string">&quot;   %5llu\n&quot;</span>,
	      (nr_table[i].cur_drops / avg_interval));
	}
	fflush(stdout);
    }
}

<span class="enscript-type">static</span> <span class="enscript-type">void</span>
<span class="enscript-function-name">print_column_heading</span>(<span class="enscript-type">int</span> type, <span class="enscript-type">char</span> *timebufptr, <span class="enscript-type">int</span> mode)
{
    <span class="enscript-type">char</span> *p;

    p = timebufptr;
    
    <span class="enscript-keyword">if</span> (p == NULL)
	p = <span class="enscript-string">&quot;Average:&quot;</span>;

    <span class="enscript-keyword">if</span> (!(flag_count &gt; 1))
      fprintf(stdout, <span class="enscript-string">&quot;\n&quot;</span>);

    <span class="enscript-keyword">switch</span> (type)
    {
    <span class="enscript-keyword">case</span> <span class="enscript-reference">SAR_CPU</span>:
    	fprintf (stdout, <span class="enscript-string">&quot;\n%s  %%usr  %%nice   %%sys   %%idle\n&quot;</span>, p);
	<span class="enscript-keyword">break</span>;
	
    <span class="enscript-keyword">case</span> <span class="enscript-reference">SAR_VMSTAT</span>:
	<span class="enscript-keyword">if</span> (mode == 0)  <span class="enscript-comment">/* gflag */</span>
	    fprintf(stdout, <span class="enscript-string">&quot;\n%s    pgout/s\n&quot;</span>, p);
	<span class="enscript-keyword">else</span> <span class="enscript-keyword">if</span> (mode == 1)  <span class="enscript-comment">/* pflag */</span>
	    fprintf(stdout, <span class="enscript-string">&quot;\n%s     pgin/s        pflt/s        vflt/s\n&quot;</span>, p);	    
	<span class="enscript-keyword">break</span>;	
    <span class="enscript-keyword">case</span> <span class="enscript-reference">SAR_DRIVESTATS</span>:
	fprintf(stdout, <span class="enscript-string">&quot;\n%s   device    r+w/s    blks/s\n&quot;</span>, p);	
	<span class="enscript-keyword">break</span>;
    <span class="enscript-keyword">case</span> <span class="enscript-reference">SAR_NETSTATS</span>:
	<span class="enscript-keyword">if</span> (mode == NET_DEV_MODE)
	{	    
	    fprintf(stdout, <span class="enscript-string">&quot;\n%s %-8.8s   %8.8s    %10.10s    %8.8s    %10.10s\n&quot;</span>, p,
	      <span class="enscript-string">&quot;   IFACE&quot;</span>, <span class="enscript-string">&quot;Ipkts/s&quot;</span>, <span class="enscript-string">&quot;Ibytes/s&quot;</span>, <span class="enscript-string">&quot;Opkts/s&quot;</span>, <span class="enscript-string">&quot;Obytes/s&quot;</span>);
	}
	<span class="enscript-keyword">else</span> <span class="enscript-keyword">if</span> (mode == NET_EDEV_MODE)
	{
	    fprintf(stdout, <span class="enscript-string">&quot;\n%s %-8.8s     %7.7s     %7.7s    %5s      %s\n&quot;</span>, p,
	      <span class="enscript-string">&quot;   IFACE&quot;</span>, <span class="enscript-string">&quot;Ierrs/s&quot;</span>, <span class="enscript-string">&quot;Oerrs/s&quot;</span>, <span class="enscript-string">&quot;Coll/s&quot;</span>, <span class="enscript-string">&quot;Drop/s&quot;</span>);
	}
	<span class="enscript-keyword">break</span>;	
    <span class="enscript-reference">default</span>:
	<span class="enscript-keyword">break</span>;
    }
}

</pre>
<hr />
</body></html>