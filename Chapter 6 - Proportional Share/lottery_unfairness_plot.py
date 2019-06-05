#! /usr/bin/env python
import sys
import random
import operator
from optparse import OptionParser
import seaborn as sns
import matplotlib.pyplot as plt

parser = OptionParser()
parser.add_option('-s', '--seed', default=0, help='the random seed',              action='store', type='int', dest='seed')
parser.add_option('-j', '--jobs', default=3, help='number of jobs in the system', action='store', type='int', dest='jobs')
parser.add_option('-l', '--jlist', default='', help='instead of random jobs, provide a comma-separated list of run times and ticket values (e.g., 10:100,20:100 would have two jobs with run-times of 10 and 20, each with 100 tickets)',  action='store', type='string', dest='jlist')
parser.add_option('-m', '--maxlen',  default=10,  help='max length of job',         action='store', type='int', dest='maxlen')
parser.add_option('-T', '--maxticket', default=100, help='maximum ticket value, if randomly assigned',          action='store', type='int', dest='maxticket')
parser.add_option('-q', '--quantum', default=1,   help='length of time slice', action='store', type='int', dest='quantum')
parser.add_option('-c', '--compute', help='compute answers for me', action='store_true', default=False, dest='solve')

(options, args) = parser.parse_args()

random.seed(options.seed)


print('ARG jlist', options.jlist)
print('ARG jobs', options.jobs)
print('ARG maxlen', options.maxlen)
print('ARG maxticket', options.maxticket)
print('ARG quantum', options.quantum)
print('ARG seed', options.seed)

def get_unfairness_ratio(job_length, tickets=100):
    """
                              time of completion of first job
        Unfairness Ratio(n) = --------------------------------
                              time of completion of second job 
        n = job_length

        Arguments
        ---------
        int job_length: length of each job
    """
    joblist = [ 
        {
            'job': 0,
            'runtime': job_length,
            'tickets': tickets,
            'finished': 0
        },
        {
            'job': 1,
            'runtime': job_length,
            'tickets': tickets,
            'finished': 0
        }
    ]
    total_runtime  = len(joblist) * job_length 
    total_tickets = len(joblist) * tickets

    unfairness = 0

    jobs  = 2
    clock = 0

    for i in range(total_runtime):
        r = int(random.random() * 1000001)
        winner = int(r % total_tickets)

        current = 0
        for job in joblist:
            current += job['tickets']
            if current > winner:
                wjob = job
                break

        # now do the accounting
        if wjob['runtime'] >= options.quantum:
            wjob['runtime'] -= options.quantum
        else:
            wjob['runtime'] = 0

        clock += options.quantum

        # job completed!
        if wjob['runtime'] == 0:
            total_tickets -= wjob['tickets']
            wjob['tickets'] = 0
            jobs -= 1
            wjob['finished'] = clock

        # update job list
        joblist[wjob['job']] = wjob

        if jobs == 0:
            break

    finish_time_job1 = joblist[0].get('finished', 0)
    finish_time_job2 = joblist[1].get('finished', 0)
    
    # print(job_length, finish_time_job1, finish_time_job2)

    return (finish_time_job1 / finish_time_job2) if finish_time_job1 < finish_time_job2 else (finish_time_job2 / finish_time_job1)

if __name__ == '__main__':
    JOB_LENGTH = 1000
    unfairness_ratios = list()

    for job_length in range(1, JOB_LENGTH+1):
        unfairness_ratio = 0
        for seedval in range(1, 31):
            options.seed = seedval
            unfairness_ratio += get_unfairness_ratio(job_length)

        unfairness_ratio = unfairness_ratio / 30
        
        # unfairness_ratio = get_unfairness_ratio(job_length)
        unfairness_ratios.append(unfairness_ratio)
        print(job_length, unfairness_ratio)

    sns.set_style('darkgrid')
    sns.set_context('paper')
    plt.xscale('log')
    plt.plot(unfairness_ratios)
    plt.show()



