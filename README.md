# Hacking-Techniques-Tips

<p align="center">
  <img src="https://i.ibb.co/Bfdtftr/Astaroth1-removebg-preview.png">
</p>

Some techniques and tips i use for my Pentest and Bug Bounty processes.
## Recon Process

### Recon Tools
* [Amass](https://github.com/OWASP/Amass) - The OWASP Amass Project performs network mapping of attack surfaces and external asset discovery using open source information gathering and active reconnaissance techniques.
* [Assetfinder](https://github.com/tomnomnom/assetfinder) - Find domains and subdomains potentially related to a given domain.
* [Dalfox](https://github.com/hahwul/dalfox) - DalFox is an powerful open source XSS scanning tool and parameter analyzer and utility that fast the process of detecting and verify XSS flaws.
* [Dnsrecon](https://github.com/darkoperator/dnsrecon) - Very useful for dns enumeration.
* [Gobuster](https://github.com/OJ/gobuster) - Gobuster is a tool used to brute-force in URIs and Subdomains.
* [Httpx](https://github.com/projectdiscovery/httpx) - httpx is a fast and multi-purpose HTTP toolkit allow to run multiple probers using retryablehttp library, it is designed to maintain the result reliability with increased threads.
* [WaybackURLs](https://github.com/tomnomnom/waybackurls) - fetch known URLs from the Wayback Machine for *.domain and output them on stdout.

### Recon Tip
Quick search by XSS:
```
subfinder -d TARGET.COM --silent | httpx-toolkit -silent | waybackurls | grep '=' | dalfox -b https://hahwul.xss.ht
```

Quick search by XSS type 2
```
cat alvo.txt | Gxss -p art | dalfox pipe --mining-dict-word /home/arthur/Tools/params.txt --skip-bav -o teste-xss.txt
```
