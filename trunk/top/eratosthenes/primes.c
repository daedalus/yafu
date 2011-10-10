/*----------------------------------------------------------------------
This source distribution is placed in the public domain by its author,
Ben Buhrow. You may use it for any purpose, free of charge,
without having to notify anyone. I disclaim any responsibility for any
errors.

Optionally, please be nice and tell me if you find this source to be
useful. Again optionally, if you add to the functionality present here
please consider making those additions public too, so that others may 
benefit from your work.	

       				   --bbuhrow@gmail.com 7/1/10
----------------------------------------------------------------------*/

#include "soe.h"

void primes_from_lineflags(thread_soedata_t *t)
{
	//the sieve primes are not in the line array, so they must be added
	//in if necessary
	soe_staticdata_t *sdata = &t->sdata;
	soe_dynamicdata_t *ddata = &t->ddata;
	uint8 *line = t->ddata.line;
	uint64 current_line = t->current_line;
	uint64 prime, num_alloc;
	uint64 i,it;

	it=0;

	count_line(t);
	num_alloc = t->linecount;
	//printf("attempting to allocate room for %" PRIu64 " primes based on linecount\n",num_alloc);
	ddata->primes = (uint64 *)malloc((size_t)(num_alloc * sizeof(uint64)));
	if (ddata->primes == NULL)
	{
		printf("failed to allocate primes array in primes_from_lineflags\n");
		exit(-1);
	}

	//this will find all the primes in the line.  when other lines are appended, the primes
	//will be out of order and will need to be sorted.
	for (i=0; i < sdata->numlinebytes; i++)
	{
		if (line[i] == 0)
			continue;

		if (line[i] & nmasks[0])
		{
			prime = sdata->prodN * ((i << 3) + 0) + 
				sdata->rclass[current_line] + sdata->lowlimit;

			//only store the prime if it is within our requested bounds
			if ((prime >= sdata->orig_llimit) && (prime <= sdata->orig_hlimit))
			{
				ddata->primes[it] = prime;
				it++;					
			}
		}
		if (line[i] & nmasks[1])
		{
			prime = sdata->prodN * ((i << 3) + 1) + 
				sdata->rclass[current_line] + sdata->lowlimit;

			//only store the prime if it is within our requested bounds
			if ((prime >= sdata->orig_llimit) && (prime <= sdata->orig_hlimit))
			{
				ddata->primes[it] = prime;
				it++;					
			}
		}
		if (line[i] & nmasks[2])
		{
			prime = sdata->prodN * ((i << 3) + 2) + 
				sdata->rclass[current_line] + sdata->lowlimit;

			//only store the prime if it is within our requested bounds
			if ((prime >= sdata->orig_llimit) && (prime <= sdata->orig_hlimit))
			{
				ddata->primes[it] = prime;
				it++;					
			}
		}
		if (line[i] & nmasks[3])
		{
			prime = sdata->prodN * ((i << 3) + 3) + 
				sdata->rclass[current_line] + sdata->lowlimit;

			//only store the prime if it is within our requested bounds
			if ((prime >= sdata->orig_llimit) && (prime <= sdata->orig_hlimit))
			{
				ddata->primes[it] = prime;
				it++;					
			}
		}
		if (line[i] & nmasks[4])
		{
			prime = sdata->prodN * ((i << 3) + 4) + 
				sdata->rclass[current_line] + sdata->lowlimit;

			//only store the prime if it is within our requested bounds
			if ((prime >= sdata->orig_llimit) && (prime <= sdata->orig_hlimit))
			{
				ddata->primes[it] = prime;
				it++;					
			}
		}
		if (line[i] & nmasks[5])
		{
			prime = sdata->prodN * ((i << 3) + 5) + 
				sdata->rclass[current_line] + sdata->lowlimit;

			//only store the prime if it is within our requested bounds
			if ((prime >= sdata->orig_llimit) && (prime <= sdata->orig_hlimit))
			{
				ddata->primes[it] = prime;
				it++;					
			}
		}
		if (line[i] & nmasks[6])
		{
			prime = sdata->prodN * ((i << 3) + 6) + 
				sdata->rclass[current_line] + sdata->lowlimit;

			//only store the prime if it is within our requested bounds
			if ((prime >= sdata->orig_llimit) && (prime <= sdata->orig_hlimit))
			{
				ddata->primes[it] = prime;
				it++;					
			}
		}
		if (line[i] & nmasks[7])
		{
			prime = sdata->prodN * ((i << 3) + 7) + 
				sdata->rclass[current_line] + sdata->lowlimit;

			//only store the prime if it is within our requested bounds
			if ((prime >= sdata->orig_llimit) && (prime <= sdata->orig_hlimit))
			{
				ddata->primes[it] = prime;
				it++;					
			}
		}
	}

	if (it != t->linecount)
		printf("warning, counts do not match after computing primes\n");

	t->linecount = it;

	return;
}

uint64 * merge_primes(uint64 *mergeprimes, uint64 *locprimes, 
	uint64 num_p, uint64 linecount)
{
	//num_p is the size of mergeprimes
	//linecount is the size of locprimes

	//merge locprimes into mergeprimes.  
	uint64 i1, i2, i3;
	uint64 *new_merge;
	
	new_merge = (uint64 *)malloc((num_p + linecount) * sizeof(uint64));

	i1 = i2 = i3 = 0;
	while ((i1 < num_p) && (i2 < linecount)) {
		if (mergeprimes[i1] < locprimes[i2])
			new_merge[i3++] = mergeprimes[i1++];
		else
			new_merge[i3++] = locprimes[i2++];
	}
	while (i1 < num_p)
		new_merge[i3++] = mergeprimes[i1++];

	while (i2 < linecount)
		new_merge[i3++] = locprimes[i2++];						

	return new_merge;
}

uint64 * merge_primes32(uint64 *mergeprimes, uint32 *locprimes, 
	uint64 num_p, uint64 linecount)
{
	//num_p is the size of mergeprimes
	//linecount is the size of locprimes

	//merge locprimes into mergeprimes.  
	uint64 i1, i2, i3;
	uint64 *new_merge;
	
	new_merge = (uint64 *)malloc((num_p + linecount) * sizeof(uint64));

	i1 = i2 = i3 = 0;
	while ((i1 < num_p) && (i2 < linecount)) {
		if (mergeprimes[i1] < (uint64)locprimes[i2])
			new_merge[i3++] = mergeprimes[i1++];
		else
			new_merge[i3++] = (uint64)locprimes[i2++];
	}
	while (i1 < num_p)
		new_merge[i3++] = mergeprimes[i1++];

	while (i2 < linecount)
		new_merge[i3++] = (uint64)locprimes[i2++];						

	return new_merge;
}

