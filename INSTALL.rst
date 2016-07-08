Requirements on Ubuntu 14.04
----------------------------


.. code-block:: sh

    sudo apt-get install libncursesw5-dev  build-essential libtool

    sudo apt-get install software-properties-common
    sudo add-apt-repository ppa:george-edison55/cmake-3.x
    sudo apt-get update -y
    sudo apt-get upgrade cmake   # if cmake installed already
    sudo apt-get install cmake   # if not installed
