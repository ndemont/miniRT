/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:21:44 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/04 13:29:29 by ndemont          ###   ########.fr       */
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
    bmph->sizeOfBmpFile = 54 + (3 * s->R[0] * s->R[1]);
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
    bmpi->colorDepth = 24;
    write(fd, &bmpi->colorDepth, 2);
    bmpi->compressionMethod = 0;
    write(fd, &bmpi->compressionMethod, 4);
    bmpi->rawBitmapDataSize = 0;
    write(fd, &bmpi->rawBitmapDataSize, 4);
    bmpi->horizontalResolution = 3780;
    write(fd, &bmpi->horizontalResolution, 4);
    bmpi->verticalResolution = 3780;
    write(fd, &bmpi->verticalResolution, 4);
    bmpi->colorTableEntries = 0;
    write(fd, &bmpi->colorTableEntries, 4);
    bmpi->importantColors = 0;
    write(fd, &bmpi->importantColors, 4);
}

void    ft_fill_pixel(t_pixel *pixel, int fd, t_scene *s) 
{
    (void)s;
    pixel->blue = (char)200;
    write(fd, &pixel->blue, 1);
    pixel->green = (char)55;
    write(fd, &pixel->green, 1);
    pixel->red = (char)200;
    write(fd, &pixel->red, 1);
}

int bmp_yay(t_scene *s) 
{
    t_BmpHeader     bmph;
    t_bmpInfoHeader bmpi;
    t_pixel         pixel;
    int             pixel_nbr;
    int             fd;
    int             i;

    fd = open("file.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd < 0)
        return (printf("Error: can not open file.\n"));
    ft_fill_bmph(&bmph, fd, s);
    ft_fill_bmpinfo(&bmpi, fd, s);
    ft_fill_pixel(&pixel, fd, s);
    pixel_nbr = s->R[0] * s->R[1];
    i = 0;
    while (i < pixel_nbr)
    {
        ft_fill_pixel(&pixel, fd, s);
        i++;
    }
    close(fd);
    return 0;
}