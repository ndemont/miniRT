/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:21:44 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/04 17:24:30 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include <fcntl.h>
 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include "minirt.h"

void    ft_fill_bmph(t_BmpHeader *bmph, int fd, t_scene *s)
{
    bmph->bitmapSbytes[0] = 'B';
    write(fd, &bmph->bitmapSbytes[0], 1);
    bmph->bitmapSbytes[1] = 'M';
    write(fd, &bmph->bitmapSbytes[1], 1);
    bmph->sizeOfBmpFile = 54 + (4 * s->R[0] * s->R[1]);
    //bmph->sizeOfBmpFile = 54 + 786432;
    write(fd, &bmph->sizeOfBmpFile, 4);
    bmph->reservedBytes = 0;
    write(fd, &bmph->reservedBytes, 4);
    bmph->pixelDataOffset = 54;
    write(fd, &bmph->pixelDataOffset, 4);
}

void    ft_fill_bmpinfo(t_bmpInfoHeader *bmpi, int fd, t_scene *s)
{
    bmpi->sizeOfThisHeader = 40;
    write(fd, &bmpi->sizeOfThisHeader, 4);
    bmpi->width = s->R[0];
    write(fd, &bmpi->width, 4);
    bmpi->height = s->R[1];
    write(fd, &bmpi->height, 4);
    bmpi->numberOfColorPlanes = 1;
    write(fd, &bmpi->numberOfColorPlanes, 2);
    bmpi->colorDepth = 32;
    write(fd, &bmpi->colorDepth, 2);
    bmpi->compressionMethod = 0;
    write(fd, &bmpi->compressionMethod, 4);
    bmpi->rawBitmapDataSize = 0;
    write(fd, &bmpi->rawBitmapDataSize, 4);
    bmpi->horizontalResolution = 0;
    write(fd, &bmpi->horizontalResolution, 4);
    bmpi->verticalResolution = 0;
    write(fd, &bmpi->verticalResolution, 4);
    bmpi->colorTableEntries = 0;
    write(fd, &bmpi->colorTableEntries, 4);
    bmpi->importantColors = 0;
    write(fd, &bmpi->importantColors, 4);
}

void    ft_fill_pixel(int fd, t_scene *s, int pxl) 
{
    int i;
    int y;
    char c;
    int size;
    int count;

    i = 0;
    y = (pxl * 4) - 1;
    c = 0;
    while (i < pxl)
    {
        size = s->size_line - 4;
        count = 0;
        printf("size_line = %d\n", s->size_line);
        while (count < s->size_line / 4)
        {
            
            write(fd, &s->data_addr[y - 3 - size], 1); // pixel bleu
            write(fd, &s->data_addr[y - 2 - size], 1); // pixel vert
            write(fd, &s->data_addr[y - 1 - size], 1); // pixel rouge
            write(fd, &c, 1);
            y = y - 4;
            size = size - 8;
            count++;
            i++;
        }
        // write(fd, &s->data_addr[y - 3], 1); // pixel bleu
        // write(fd, &s->data_addr[y - 2], 1); // pixel vert
        // write(fd, &s->data_addr[y - 1], 1); // pixel rouge
        // write(fd, &c, 1);
        // y = y - 4;
        // i++;
    }
}

int bmp_yay(t_scene *s) 
{
    t_BmpHeader     bmph;
    t_bmpInfoHeader bmpi;
    //t_pixel         pixel;
    int             pixel_nbr;
    int             fd;
    //int             i;

    fd = open("file.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd < 0)
        return (printf("Error: can not open file.\n"));
    ft_fill_bmph(&bmph, fd, s);
    ft_fill_bmpinfo(&bmpi, fd, s);
    //ft_fill_pixel(&pixel, fd, s);
    pixel_nbr = s->R[0] * s->R[1];
    ft_fill_pixel(fd, s, pixel_nbr);
    close(fd);
    return 0;
}