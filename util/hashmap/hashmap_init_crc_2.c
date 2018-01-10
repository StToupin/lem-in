/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_init_crc_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:59:25 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 14:59:27 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	hashmap_init_crc_200_224(unsigned long *tab)
{
	tab[200] = 0x95bf4a82L;
	tab[201] = 0xe2b87a14L;
	tab[202] = 0x7bb12baeL;
	tab[203] = 0x0cb61b38L;
	tab[204] = 0x92d28e9bL;
	tab[205] = 0xe5d5be0dL;
	tab[206] = 0x7cdcefb7L;
	tab[207] = 0x0bdbdf21L;
	tab[208] = 0x86d3d2d4L;
	tab[209] = 0xf1d4e242L;
	tab[210] = 0x68ddb3f8L;
	tab[211] = 0x1fda836eL;
	tab[212] = 0x81be16cdL;
	tab[213] = 0xf6b9265bL;
	tab[214] = 0x6fb077e1L;
	tab[215] = 0x18b74777L;
	tab[216] = 0x88085ae6L;
	tab[217] = 0xff0f6a70L;
	tab[218] = 0x66063bcaL;
	tab[219] = 0x11010b5cL;
	tab[220] = 0x8f659effL;
	tab[221] = 0xf862ae69L;
	tab[222] = 0x616bffd3L;
	tab[223] = 0x166ccf45L;
	tab[224] = 0xa00ae278L;
}

void	hashmap_init_crc_225_249(unsigned long *tab)
{
	tab[225] = 0xd70dd2eeL;
	tab[226] = 0x4e048354L;
	tab[227] = 0x3903b3c2L;
	tab[228] = 0xa7672661L;
	tab[229] = 0xd06016f7L;
	tab[230] = 0x4969474dL;
	tab[231] = 0x3e6e77dbL;
	tab[232] = 0xaed16a4aL;
	tab[233] = 0xd9d65adcL;
	tab[234] = 0x40df0b66L;
	tab[235] = 0x37d83bf0L;
	tab[236] = 0xa9bcae53L;
	tab[237] = 0xdebb9ec5L;
	tab[238] = 0x47b2cf7fL;
	tab[239] = 0x30b5ffe9L;
	tab[240] = 0xbdbdf21cL;
	tab[241] = 0xcabac28aL;
	tab[242] = 0x53b39330L;
	tab[243] = 0x24b4a3a6L;
	tab[244] = 0xbad03605L;
	tab[245] = 0xcdd70693L;
	tab[246] = 0x54de5729L;
	tab[247] = 0x23d967bfL;
	tab[248] = 0xb3667a2eL;
	tab[249] = 0xc4614ab8L;
}

void	hashmap_init_crc_250_255(unsigned long *tab)
{
	tab[250] = 0x5d681b02L;
	tab[251] = 0x2a6f2b94L;
	tab[252] = 0xb40bbe37L;
	tab[253] = 0xc30c8ea1L;
	tab[254] = 0x5a05df1bL;
	tab[255] = 0x2d02ef8dL;
}
