# Análise de Ciclo de Vida de Sockets e Exaustão de Recursos em C

Este repositório foi criado exclusivamente para fins didáticos e laboratoriais de engenharia reversa de protocolos. O objetivo deste projeto é explorar o comportamento de baixo nível da biblioteca de sockets do Linux (`sys/socket.h`) e analisar como os sistemas operacionais gerenciam buffers de conexão e descritores de arquivos abertos.

## 📌 Descrição do Estudo

O código desenvolvido em C interage diretamente com a API de redes do sistema operacional para iniciar conexões TCP estruturadas na porta do serviço FTP (Porta 21). Diferente de utilitários de alto nível, este programa estuda o impacto de conexões mantidas ativas sem a transmissão imediata do sinal de encerramento (`close()`).

### Conceitos de Rede Explorados:
* **`socket()`**: Alocação de novos descritores de arquivos (File Descriptors) para comunicação de rede.
* **`struct sockaddr_in`**: Estruturação manual de endereços IP (usando `inet_addr`) e conversão de portas para ordem de bytes da rede (usando `htons`).
* **`connect()`**: Iniciação do aperto de mão de três vias (TCP Three-Way Handshake).

---

## 🛠️ Como o Sistema Operacional Gerencia os Recursos

Quando múltiplas chamadas `connect()` são feitas consecutivamente sem que o cliente envie um pacote `FIN` ou `RST`, o sistema operacional do servidor precisa manter o estado da conexão na memória (geralmente no estado `ESTABLISHED`). 

Isso consome recursos críticos do Kernel do Linux:
1. **Tabela de File Descriptors:** Cada socket ativo ocupa uma entrada na tabela de arquivos do sistema.
2. **Memória de Buffer (TCP Buffers):** O sistema reserva espaço de memória RAM (`rmem` e `wmem`) para gerenciar as filas de dados de cada conexão pendente.

---

## 🛡️ Mecanismos de Defesa e Mitigação

A existência de códigos estruturados dessa forma destaca a importância de configurar corretamente as defesas de infraestrutura. Sistemas de produção modernos mitigam a exaustão de conexões através das seguintes abordagens:

### 1. Ajustes de Kernel (sysctl)
Administradores de sistemas configuram parâmetros de rede no `/etc/sysctl.conf` para liberar recursos rapidamente:
* `net.ipv4.tcp_fin_timeout`: Reduz o tempo que uma conexão órfã permanece aberta aguardando encerramento.
* `net.ipv4.tcp_max_syn_backlog`: Limita o tamanho da fila de conexões pendentes antes de descartar novas requisições.

### 2. Limitação de Recursos por Processo (ulimit)
O Linux impõe limites de quantos arquivos/sockets um único processo pode manipular simultaneamente através do comando `ulimit -n`. Caso o programa atinja o limite padrão (normalmente 1024), o sistema operacional impede a criação de novas conexões retornando o erro `EMFILE (Too many open files)`.

### 3. Rate Limiting e Firewalls Ativos
O uso de ferramentas defensivas como o **iptables** ou **nftables** permite bloquear conexões excessivas vindas de uma mesma origem:
```bash
# Exemplo de regra iptables para limitar conexões simultâneas na porta 21 por IP
iptables -A INPUT -p tcp --syn --dport 21 -m connlimit --connlimit-above 10 -j REJECT




(ISSO FOI ESCRITO COM IA, POIS ESTAVA COM PREGUICA DE EXPLICAR OQ O PROGRAMA FAZIA, MAS SE VC JA CONHECE UM POUCO DA AREA DE CYBERSECURITY JA VAI SABER OQ E PELO NOME DOS FPT)
