struct vectores{
        int array1[20];
        int array2[20];
        int arr1len;
        int arr2len;
};

program PROG_OP{
        version VERS_OP{
                int productoPunto(vectores) = 1;
                double medioRangoEspecial(vectores) = 2;
        }=1;
}= 0x20000001;