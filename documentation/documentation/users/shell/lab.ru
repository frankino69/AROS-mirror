===
Lab
===

.. This document is automatically generated. Don't edit it!

`Index <index>`_ `Prev <join>`_ `Next <list>`_ 

---------------

::

 Lab 

������������
~~~~~~~~~~~~
::


     Workbench:C


�������
~~~~~~~
::

     ���������� ����� � �������. �� ��� ������ ����� ��������� ��� �������������
     ������� Skip.
     

�������
~~~~~~~
::


    If NOT EXISTS S:User-Startup
        Skip NoUserSeq
    EndIf

    FailAt 20
    Execute S:User-Startup
    Quit

    Lab NoUserSeq
    Echo "No User-Startup found"


��. �����
~~~~~~~~~
::


    Skip


