<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>sar.h</title>
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
<h1 style="margin:8px;" id="f1">sar.h&nbsp;&nbsp;&nbsp;<span style="font-weight: normal; font-size: 0.5em;">[<a href="sar.h">plain text</a>]</span></h1>
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

#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;CoreFoundation/CoreFoundation.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;IOKit/IOKitLib.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;IOKit/storage/IOBlockStorageDriver.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;IOKit/storage/IOMedia.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;IOKit/IOBSD.h&gt;</span>

#<span class="enscript-reference">define</span> <span class="enscript-variable-name">MAXDRIVENAME</span> 31  <span class="enscript-comment">/* largest drive name we allow */</span>


<span class="enscript-type">struct</span> drivestats_report
{
	<span class="enscript-type">char</span>		*next;
	int32_t		present;
	int32_t		avg_count;
	int32_t		drivepath_id;
	<span class="enscript-type">char</span>		name[MAXDRIVENAME+1];
	uint64_t	blocksize;
    
	uint64_t	cur_Reads;
	uint64_t	prev_Reads;
	uint64_t	avg_Reads;
    
	uint64_t	cur_BytesRead;
	uint64_t	prev_BytesRead;
	uint64_t	avg_BytesRead;

	uint64_t	cur_Writes;
	uint64_t	prev_Writes;
	uint64_t	avg_Writes;
    
	uint64_t	cur_BytesWritten;
	uint64_t	prev_BytesWritten;
	uint64_t	avg_BytesWritten;
    
	uint64_t	cur_LatentReadTime;
	uint64_t	prev_LatentReadTime;
	uint64_t	avg_LatentReadTime;
    
	uint64_t	cur_LatentWriteTime;
	uint64_t	prev_LatentWriteTime;
	uint64_t	avg_LatentWriteTime;
    
	uint64_t	cur_ReadErrors;
	uint64_t	prev_ReadErrors;
	uint64_t	avg_ReadErrors;
    
	uint64_t	cur_WriteErrors;
	uint64_t	prev_WriteErrors;
	uint64_t	avg_WriteErrors;
    
	uint64_t	cur_ReadRetries;
	uint64_t	prev_ReadRetries;
	uint64_t	avg_ReadRetries;
    
	uint64_t	cur_WriteRetries;
	uint64_t	prev_WriteRetries;
	uint64_t	avg_WriteRetries;    

	uint64_t	cur_TotalReadTime;
	uint64_t	prev_TotalReadTime;
	uint64_t	avg_TotalReadTime;
    
	uint64_t	cur_TotalWriteTime;
	uint64_t	prev_TotalWriteTime;
	uint64_t	avg_TotalWriteTime;    
};

<span class="enscript-type">struct</span> netstats_report
{
	int32_t		valid;
	int32_t		present;
	int32_t		avg_count;
	uint32_t	gen_counter;
	<span class="enscript-type">char</span>		tname_unit[MAX_TNAME_UNIT_SIZE +1 ];

	uint64_t	cur_ipackets;
	uint64_t	prev_ipackets;
	uint64_t	avg_ipackets;
    
	uint64_t	cur_ierrors;
	uint64_t	prev_ierrors;
	uint64_t	avg_ierrors;    
    
	uint64_t	cur_opackets;
	uint64_t	prev_opackets;
	uint64_t	avg_opackets;

	uint64_t	cur_oerrors;
	uint64_t	prev_oerrors;
	uint64_t	avg_oerrors;    
    
	uint64_t	cur_collisions;
	uint64_t	prev_collisions;
	uint64_t	avg_collisions;

	uint64_t	cur_ibytes;
	uint64_t	prev_ibytes;
	uint64_t	avg_ibytes;
    
	uint64_t	cur_obytes;
	uint64_t	prev_obytes;
	uint64_t	avg_obytes;
    
	uint64_t	cur_imcasts;
	uint64_t	prev_imcasts;
	uint64_t	avg_imcasts;

	uint64_t	cur_omcasts;
	uint64_t	prev_omcasts;
	uint64_t	avg_omcasts;

	uint64_t	cur_drops;
	uint64_t	prev_drops;
	uint64_t	avg_drops;
};
</pre>
<hr />
</body></html>