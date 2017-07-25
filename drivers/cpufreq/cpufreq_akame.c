/*
 * drivers/cpufreq/cpufreq_akame.c
 *
 * Copyright (C) 2010 Google, Inc.
 *
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
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/cpufreq.h>
#include <linux/init.h>
#include <linux/module.h>

static int cpufreq_governor_akame(struct cpufreq_policy *policy,
					unsigned int event)
{
	switch (event) {
	case CPUFREQ_GOV_START:
	case CPUFREQ_GOV_LIMITS:
		pr_debug("setting to %u kHz because of event %u\n",
						policy->max, event);
		__cpufreq_driver_target(policy, policy->max,
						CPUFREQ_RELATION_H);
		break;
	default:
		break;
	}
	return 0;
}

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
