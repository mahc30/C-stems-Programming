struct arrays{
        int arr1[50];
        int arr2[50];
        int arr1len;
        int arr2len;
};

program PROG_MAHC{
        version VERS_MAHC{
                int productoPunto(arrays) = 1;
                double medioRangoEspecial(arrays) = 2;
        }=1;
} = 0x20000001;
