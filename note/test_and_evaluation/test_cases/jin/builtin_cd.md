

```shell
echo $PWD; echo $OLDPWD; cd .; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ../..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ../../..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ../../../..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ../../../../..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ../../../../../..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /; pwd; echo $PWD; echo $OLDPWD
# /etc is a link to /etc/private
# hard and weird to implement with pwd
# cd /etc; pwd; echo $PWD
echo $PWD; echo $OLDPWD; cd ''; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd '' ''; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd '' '' ''; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ' '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd d ''; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd d d; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd d ' '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd $HOME; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /.; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /./; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /././././; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd //; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ///; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ////; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd //////////////////////////////////////////////////////; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ' /'; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ' / '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd '                  /'; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd '                  /              '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ' // '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd //home; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ' //home'; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd '     //home    '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD
```