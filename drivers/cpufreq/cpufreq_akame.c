/*
 * drivers/cpufreq/cpufreq_akame.c
 *
 * Copyright (C) 2010 Google, Inc.
 * Copyright (C) 2017 Renaldy P
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Author: Renaldy P (aerozox01@gmail.com)
 * Added module interface 
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/cpufreq.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cpu.h>
#include <linux/jiffies.h>
#include <linux/kernel_stat.h>
#include <linux/mutex.h>
#include <linux/hrtimer.h>
#include <linux/tick.h>
#include <linux/ktime.h>
#include <linux/sched.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <linux/slab.h>

#define cpuinfo_max_freq (1440000)
#define cpuinfo_min_freq (400000)
#define sampling_rate (2)
#define sleep_wakeup_freq (1248000)
#define sched_boost_active (1)
#define sync_threshold (1305000)
#define SAMPLING_RATE (48)
#define SAMPLING_RATE_MIN (40)
#define SAPLING_RATE_US (90)
#define DEFAULT_TARGET_LOAD (80)

struct cpufreq_akame_cpuinfo {
	struct timer_list cpu_idle;
	struct timer_list cpu_timer;
	struct timer_list cpu_slack_timer;
	u64 time_in_idle;
	u64 timer_create;
	u64 timer_gettime;
	u64 timer_pending;
	u64 timer_settime;
	u64 timer_delete;
	struct cpufreq_policy *policy;
	struct cpufreq_frequency_table *freq_table;	
};

/* Default target loads */
int default_target_loads[] = {DEFAULT_TARGET_LOAD};

/* Minimum Sampling Rate */
int sampling_rate_min[] = {SAMPLING_RATE_MIN};

/*Sampling Rate */
int sampling_rate[] = {SAMPLING_RATE};

/* Sample rate jiffies */
int AKAME_SAMPLE_RATE_JIFFIES[] = {sampling_rate};

/* Set the maximum frequency when device is awake */
int AKAME_SLEEP_WAKEUP_FREQ[] = {sleep_wakeup_freq};

/* Enable sched boost */
int AKAME_SCHED_BOOST[] = {sched_boost_active};

/* Set the sync threshold */
int AKAME_SYNC_THRESHOLD[] = {sync_threshold};

/* Maximum frequency threshold */
static unsigned int CPUINFO_MAX_FREQ[] = {cpuinfo_max_freq};

/* Minimum frequency threshold */
static unsigned int CPUINFO_MIN_FREQ[] = {cpuinfo_min_freq};

static int akame_version = 1.0;
module_param_named(
	akame_governor_version, akame_version
	int, S_IRUSR | S_IWUSR
);

static int akame_author = zomaru-kun;
module_param_named(
	akame_governor_author, akame_author
	int, S_IRUSR | S_IWUSR
);

#ifdef CONFIG_CPU_FREQ_GOV_AKAME_MODULE
static
#endif
struct cpufreq_governor cpufreq_gov_akame = {
	.name		= "akame",
	.governor	= cpufreq_governor_akame,
	.owner		= THIS_MODULE,
};

static int __init cpufreq_gov_akame_init(void)
{
	return cpufreq_register_governor(&cpufreq_gov_akame);
}

static void __exit cpufreq_gov_akame_exit(void)
{
	cpufreq_unregister_governor(&cpufreq_gov_akame);
}

MODULE_AUTHOR("Renaldy P <aerozox01@gmail.com>");
MODULE_DESCRIPTION("CPUfreq policy governor 'akame'");
MODULE_LICENSE("GPL");

fs_initcall(cpufreq_gov_akame_init);
module_exit(cpufreq_gov_akame_exit);
