#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "Code/IOManagement.h"
#include "Code/ManualGPIO.h"

//
//uint8_t *buffer;
//int sizeoffile;
//static int xioctl(int fd, int request, void *arg)
//{
//    int r;
//
//    do r = ioctl (fd, request, arg);
//    while (-1 == r && EINTR == errno);
//
//    return r;
//}
//
//int print_caps(int fd)
//{
//    struct v4l2_capability caps = {};
//    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &caps))
//    {
//        perror("Querying Capabilities");
//        return 1;
//    }
//
//    printf( "Driver Caps:\n"
//            "  Driver: \"%s\"\n"
//            "  Card: \"%s\"\n"
//            "  Bus: \"%s\"\n"
//            "  Version: %d.%d\n"
//            "  Capabilities: %08x\n",
//            caps.driver,
//            caps.card,
//            caps.bus_info,
//            (caps.version>>16)&&0xff,
//            (caps.version>>24)&&0xff,
//            caps.capabilities);
//
//
//    struct v4l2_cropcap cropcap = {0};
//    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//    if (-1 == xioctl (fd, VIDIOC_CROPCAP, &cropcap))
//    {
//        perror("Querying Cropping Capabilities");
//        return 1;
//    }
//
//    printf( "Camera Cropping:\n"
//            "  Bounds: %dx%d+%d+%d\n"
//            "  Default: %dx%d+%d+%d\n"
//            "  Aspect: %d/%d\n",
//            cropcap.bounds.width, cropcap.bounds.height, cropcap.bounds.left, cropcap.bounds.top,
//            cropcap.defrect.width, cropcap.defrect.height, cropcap.defrect.left, cropcap.defrect.top,
//            cropcap.pixelaspect.numerator, cropcap.pixelaspect.denominator);
//
//    int support_grbg10 = 0;
//
//    struct v4l2_fmtdesc fmtdesc = {0};
//    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//    char fourcc[5] = {0};
//    char c, e;
//    printf("  FMT : CE Desc\n--------------------\n");
//    while (0 == xioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc))
//    {
//        strncpy(fourcc, (char *)&fmtdesc.pixelformat, 4);
//        if (fmtdesc.pixelformat == V4L2_PIX_FMT_SGRBG10)
//            support_grbg10 = 1;
//        c = fmtdesc.flags & 1? 'C' : ' ';
//        e = fmtdesc.flags & 2? 'E' : ' ';
//        printf("  %s: %c%c %s\n", fourcc, c, e, fmtdesc.description);
//        fmtdesc.index++;
//    }
//    /*
//    if (!support_grbg10)
//    {
//        printf("Doesn't support GRBG10.\n");
//        return 1;
//    }*/
//
//    struct v4l2_format fmt = {0};
//    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//    fmt.fmt.pix.width = 1980;
//    fmt.fmt.pix.height = 1080;
//    //fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_BGR24;
//    //fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_GREY;
//    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
//    fmt.fmt.pix.field = V4L2_FIELD_NONE;
//
//    if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
//    {
//        perror("Setting Pixel Format");
//        return 1;
//    }
//
//    strncpy(fourcc, (char *)&fmt.fmt.pix.pixelformat, 4);
//    printf( "Selected Camera Mode:\n"
//            "  Width: %d\n"
//            "  Height: %d\n"
//            "  PixFmt: %s\n"
//            "  Field: %d\n",
//            fmt.fmt.pix.width,
//            fmt.fmt.pix.height,
//            fourcc,
//            fmt.fmt.pix.field);
//    return 0;
//}
//
//int init_mmap(int fd)
//{
//    struct v4l2_requestbuffers req = {0};
//    req.count = 1;
//    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//    req.memory = V4L2_MEMORY_MMAP;
//
//    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req))
//    {
//        perror("Requesting Buffer");
//        return 1;
//    }
//
//    struct v4l2_buffer buf = {0};
//    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//    buf.memory = V4L2_MEMORY_MMAP;
//    buf.index = 0;
//    if(-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
//    {
//        perror("Querying Buffer");
//        return 1;
//    }
//
//    buffer = mmap (NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
//    sizeoffile = buf.length;
//    printf("Length: %d\nAddress: %p\n", buf.length, buffer);
//    printf("Image Length: %d\n", buf.bytesused);
//
//    return 0;
//}
//
//int capture_image(int fd, char *string)
//{
//    struct v4l2_buffer buf = {0};
//    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//    buf.memory = V4L2_MEMORY_MMAP;
//    buf.index = 0;
//    if(-1 == xioctl(fd, VIDIOC_QBUF, &buf))
//    {
//        perror("Query Buffer");
//        return 1;
//    }
//
//    if(-1 == xioctl(fd, VIDIOC_STREAMON, &buf.type))
//    {
//        perror("Start Capture");
//        return 1;
//    }
//
//    fd_set fds;
//    FD_ZERO(&fds);
//    FD_SET(fd, &fds);
//    struct timeval tv = {0};
//    tv.tv_sec = 2;
//    int r = select(fd+1, &fds, NULL, NULL, &tv);
//    if(-1 == r)
//    {
//        perror("Waiting for Frame");
//        return 1;
//    }
//
//    if(-1 == xioctl(fd, VIDIOC_DQBUF, &buf))
//    {
//        perror("Retrieving Frame");
//        return 1;
//    }
//    printf ("saving image\n");
//    FILE * file2 = fopen("test2.jpeg","wb");
//    printf("%d",sizeoffile);
//    fwrite(buffer,sizeoffile,1,file2);
//    fclose(file2);
//
////    IplImage* frame;
////    CvMat cvmat = cvMat(480, 640, CV_8UC3, (void*)buffer);
////    frame = cvDecodeImage(&cvmat, 1);
////    cvNamedWindow("window",CV_WINDOW_AUTOSIZE);
////    cvShowImage("window", frame);
////    cvWaitKey(0);
////    cvSaveImage("image.jpg", frame, 0);
//
//    return 0;
//}

int main()
{
// pinMode(23,1);
// int result =digitalRead(23);
// int prev_result = result;
// while (1){
//     result = digitalRead(23);
//     if (result!= prev_result) {
//         printf("changed to value %d", result);
//         prev_result = result;
//         sleep(0.1);
//     }
//    }
//    printf("test");
    int array[] = {23,24,35};
    set_gpio_list(array,3);
    execute_monitoring();
//    char array[20];
//    int prueba = 1000;
//    snprintf(array,10,"%d",prueba);
//    printf("test es %s",array);
//    printf("El largo fue %d",strlen(array));


    return 0;
}
