EO11.dll - dll-ul de interfatare cu framework-ul oferit. Un exemplu de integrare in limbajul C++ este oferit in fisierul EO11Sample.cpp
	     EO11Sample.exe fiind binarul rezultat in urma compilarii.
EO11.h   - header-ul cu definitiile necesare integrarii EO11.dll
EO11Sample.cpp - Un sample de integrare al EO11.dll scris in limbajul C++
EO11Sample.exe - Rezultatul compilarii EO11.exe
vsdk.dll - dll necesar functionarii EO11.dll, trebuie pus langa EO11.dll
EO11TesterFramework.exe - framework-ul care ruleaza sample-urile date si la final va rula jurizarea.
				  Usage .\EO11TesterFramework.exe [--default_ransomware=$ransomwareName]
Ransim - folder cu sample-urile si testbed-urile