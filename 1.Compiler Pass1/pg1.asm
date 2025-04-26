COPY    START   100
FIRST   L       1,FIVE
        A       1,=F'1'
        ST      1,TEMP
SECOND  L       2,=F'5'
        A       2,=F'2'
        ST      2,RESULT
FIVE    DC      F'5'
TEMP    DS      1F
RESULT  DS      1F
        END
