struct arrays{
        int arr1[30];
        int arr2[30];
        int arr1len;
        int arr2len;
};

program PROG_PPUNTO{
        version VERS_PPUNTO{
                int productoPunto(arrays) = 1;
                double medioRangoEspecial(arrays) = 2;
        }=1;
} = 0x20000001;
