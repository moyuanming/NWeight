#include "LocalIncludeFile.h"

int cam_fd ;
static struct jpeg_compress_struct cinfo ;
static int quality = 70 ;
static struct jpeg_error_mgr jerr ;
static unsigned char *row_rgb = NULL ;
static unsigned char *rgb = NULL ;
#define OFFSIZE_Y ((UI_DISPLAY_RESOLUTION) == (DISPPLAY_640_480) ? (55):(308))
#define OFFSIZE_X ((UI_DISPLAY_RESOLUTION) == (DISPPLAY_640_480) ? (282):(4))

static void VideoFamlloc ( int width , int height , int bpp )
{
	if ( bpp == 16 )
	{
		bpp = 2 ;
	}
	else
	{
		bpp = 4 ;
	}
	row_rgb = ( unsigned char* ) malloc ( width * 3 ) ;
	rgb = ( unsigned char* ) malloc ( width * height * bpp ) ;
	if ( !rgb || !row_rgb ) printf ("Memory Allocation Failed \n" ) ;
}
void Create_camera ( )
{
	unsigned long arg ;
	cam_fd = open ("/dev/camera" , O_RDONLY ) ;
	if ( cam_fd != -1 )
	{
		arg = OFFSIZE_Y << 16 ;
		arg += OFFSIZE_X ;
		ioctl ( cam_fd , 0x1111 , arg ) ;
		ioctl ( cam_fd , 0x2222 , arg ) ;
		VideoFamlloc ( 352 , 288 , 16 ) ;
	}
}


//static void ffree ( void )
//{
//	if ( row_rgb ) free ( row_rgb ) ;
//	if ( rgb ) free ( rgb ) ;
//}
void SaveJpg ( char * file_name , int width , int height , int bpp )
{
	int x , y ;
	FILE *jpg_fp = NULL ;
	unsigned char *base ;
	int Bytes ;
	JSAMPROW row_pointer [ 1 ] ;
	switch ( bpp )
	{
	case 16 :
		Bytes = 2 ;
		break ;
	case 24 :
		Bytes = 4 ;
		break ;
	default :
		printf ("Wrong Param BPP: %d \n" , bpp ) ;
		return ;
	}
	row_pointer [ 0 ] = ( JSAMPROW ) row_rgb ;
	/* read from device */
	if ( read ( cam_fd , rgb , width * height * Bytes ) < 0 )
	{
		perror ("read()" ) ;
		goto err ;
	}
	//sprintf ( &file_name [ 0 ] , "cap%d.jpg" , iter ) ;
	/* file create/open, note to "wb" */
	jpg_fp = fopen ( &file_name [ 0 ] , "wb" ) ;
	if ( !jpg_fp )
	{
		perror ( &file_name [ 0 ] ) ;
		goto err ;
	}
	cinfo.err = jpeg_std_error ( &jerr ) ;
	jpeg_create_compress ( &cinfo ) ;
	jpeg_stdio_dest ( &cinfo , jpg_fp ) ;
	cinfo.image_width = width ;
	cinfo.image_height = height ;
	cinfo.input_components = 3 ;
	cinfo.in_color_space = JCS_RGB ;
	jpeg_set_defaults ( &cinfo ) ;
	jpeg_set_quality ( &cinfo , quality , TRUE ) ;
	jpeg_start_compress ( &cinfo , TRUE ) ;
	if ( bpp == 16 )
	{
		/* RGB565 -> RGB888, compress */
		unsigned short *rgb16 = ( unsigned short* ) rgb ;
		for ( y = 0 ; y < height ; y++ )
		{
			base = row_rgb ;
			for ( x = 0 ; x < width ; x++ )
			{
				*base++ = ( ( * ( rgb16 + y * width + x ) & 0xf800 ) >> 8 ) & 0xff ;
				*base++ = ( ( * ( rgb16 + y * width + x ) & 0x07e0 ) >> 3 ) & 0xff ;
				*base++ = ( ( * ( rgb16 + y * width + x ) & 0x001f ) << 3 ) & 0xff ;
			}
			jpeg_write_scanlines ( &cinfo , row_pointer , 1 ) ;
		}
	}
	else
	{
		unsigned char *rgb8 ;
		unsigned char *start ;
		for ( y = 0 ; y < height ; y++ )
		{
			rgb8 = rgb + y * width * 4 ;
			start = row_rgb ;
			for ( x = 0 ; x < width * 4 ; x += 4 )
			{
				*start++ = * ( rgb8 + 2 + x ) ;
				*start++ = * ( rgb8 + 1 + x ) ;
				*start++ = * ( rgb8 + x ) ;
			}
			jpeg_write_scanlines ( &cinfo , row_pointer , 1 ) ;
		}
	}
	jpeg_finish_compress ( &cinfo ) ;
	jpeg_destroy_compress ( &cinfo ) ;
	fclose ( jpg_fp ) ;
	err : return ;
}

