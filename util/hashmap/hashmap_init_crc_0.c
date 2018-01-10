/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_init_crc_0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:59:18 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 14:59:20 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	hashmap_init_crc_000_024(unsigned long *tab)
{
	tab[0] = 0x00000000L;
	tab[1] = 0x77073096L;
	tab[2] = 0xee0e612cL;
	tab[3] = 0x990951baL;
	tab[4] = 0x076dc419L;
	tab[5] = 0x706af48fL;
	tab[6] = 0xe963a535L;
	tab[7] = 0x9e6495a3L;
	tab[8] = 0x0edb8832L;
	tab[9] = 0x79dcb8a4L;
	tab[10] = 0xe0d5e91eL;
	tab[11] = 0x97d2d988L;
	tab[12] = 0x09b64c2bL;
	tab[13] = 0x7eb17cbdL;
	tab[14] = 0xe7b82d07L;
	tab[15] = 0x90bf1d91L;
	tab[16] = 0x1db71064L;
	tab[17] = 0x6ab020f2L;
	tab[18] = 0xf3b97148L;
	tab[19] = 0x84be41deL;
	tab[20] = 0x1adad47dL;
	tab[21] = 0x6ddde4ebL;
	tab[22] = 0xf4d4b551L;
	tab[23] = 0x83d385c7L;
	tab[24] = 0x136c9856L;
}

void	hashmap_init_crc_025_049(unsigned long *tab)
{
	tab[25] = 0x646ba8c0L;
	tab[26] = 0xfd62f97aL;
	tab[27] = 0x8a65c9ecL;
	tab[28] = 0x14015c4fL;
	tab[29] = 0x63066cd9L;
	tab[30] = 0xfa0f3d63L;
	tab[31] = 0x8d080df5L;
	tab[32] = 0x3b6e20c8L;
	tab[33] = 0x4c69105eL;
	tab[34] = 0xd56041e4L;
	tab[35] = 0xa2677172L;
	tab[36] = 0x3c03e4d1L;
	tab[37] = 0x4b04d447L;
	tab[38] = 0xd20d85fdL;
	tab[39] = 0xa50ab56bL;
	tab[40] = 0x35b5a8faL;
	tab[41] = 0x42b2986cL;
	tab[42] = 0xdbbbc9d6L;
	tab[43] = 0xacbcf940L;
	tab[44] = 0x32d86ce3L;
	tab[45] = 0x45df5c75L;
	tab[46] = 0xdcd60dcfL;
	tab[47] = 0xabd13d59L;
	tab[48] = 0x26d930acL;
	tab[49] = 0x51de003aL;
}

void	hashmap_init_crc_050_074(unsigned long *tab)
{
	tab[50] = 0xc8d75180L;
	tab[51] = 0xbfd06116L;
	tab[52] = 0x21b4f4b5L;
	tab[53] = 0x56b3c423L;
	tab[54] = 0xcfba9599L;
	tab[55] = 0xb8bda50fL;
	tab[56] = 0x2802b89eL;
	tab[57] = 0x5f058808L;
	tab[58] = 0xc60cd9b2L;
	tab[59] = 0xb10be924L;
	tab[60] = 0x2f6f7c87L;
	tab[61] = 0x58684c11L;
	tab[62] = 0xc1611dabL;
	tab[63] = 0xb6662d3dL;
	tab[64] = 0x76dc4190L;
	tab[65] = 0x01db7106L;
	tab[66] = 0x98d220bcL;
	tab[67] = 0xefd5102aL;
	tab[68] = 0x71b18589L;
	tab[69] = 0x06b6b51fL;
	tab[70] = 0x9fbfe4a5L;
	tab[71] = 0xe8b8d433L;
	tab[72] = 0x7807c9a2L;
	tab[73] = 0x0f00f934L;
	tab[74] = 0x9609a88eL;
}

void	hashmap_init_crc_075_099(unsigned long *tab)
{
	tab[75] = 0xe10e9818L;
	tab[76] = 0x7f6a0dbbL;
	tab[77] = 0x086d3d2dL;
	tab[78] = 0x91646c97L;
	tab[79] = 0xe6635c01L;
	tab[80] = 0x6b6b51f4L;
	tab[81] = 0x1c6c6162L;
	tab[82] = 0x856530d8L;
	tab[83] = 0xf262004eL;
	tab[84] = 0x6c0695edL;
	tab[85] = 0x1b01a57bL;
	tab[86] = 0x8208f4c1L;
	tab[87] = 0xf50fc457L;
	tab[88] = 0x65b0d9c6L;
	tab[89] = 0x12b7e950L;
	tab[90] = 0x8bbeb8eaL;
	tab[91] = 0xfcb9887cL;
	tab[92] = 0x62dd1ddfL;
	tab[93] = 0x15da2d49L;
	tab[94] = 0x8cd37cf3L;
	tab[95] = 0xfbd44c65L;
	tab[96] = 0x4db26158L;
	tab[97] = 0x3ab551ceL;
	tab[98] = 0xa3bc0074L;
	tab[99] = 0xd4bb30e2L;
}
