Dim WshShell

Set WshShell = WScript.CreateObject("WScript.Shell")

WshShell.Run "cmd /c """""+WScript.Arguments.Item(1)+"\..\..\..\component\soc\realtek\amebad\misc\iar_utility\common\rtl8721dhp_postbuild_img1.bat"" """+WScript.Arguments.Item(0)+""" """+WScript.Arguments.Item(1)+""" """+WScript.Arguments.Item(2)+"""  >"""+WScript.Arguments.Item(1)+"\rtl8721dhp_postbuild_img1.log"" 2>&1 """, 0, true
