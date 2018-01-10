/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:59:14 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 14:59:17 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

void	hashmap_init(t_hashmap_env *env)
{
	hashmap_init_crc_000_024(env->crc32_tab);
	hashmap_init_crc_025_049(env->crc32_tab);
	hashmap_init_crc_050_074(env->crc32_tab);
	hashmap_init_crc_075_099(env->crc32_tab);
	hashmap_init_crc_100_124(env->crc32_tab);
	hashmap_init_crc_125_149(env->crc32_tab);
	hashmap_init_crc_150_174(env->crc32_tab);
	hashmap_init_crc_175_199(env->crc32_tab);
	hashmap_init_crc_200_224(env->crc32_tab);
	hashmap_init_crc_225_249(env->crc32_tab);
	hashmap_init_crc_250_255(env->crc32_tab);
}
