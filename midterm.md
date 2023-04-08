# Computer Security Midterm Summary

## Chapter 1

### Confidentiality

누가 데이터에 접근할 수 있는가?  
Access Control: **Who** can access **what**

누가 접근하려고 할 때 어떻게 확인하는가?  
Need identity(**identification**) & Need to verify identity(**Authentication**)

### Integrity

권한 없이 데이터 수정이되지 않아야 한다.  
Measure는 Context-dependent하다.

### Availability

권한 있는 사람은 언제든 데이터에 접근할 수 있는가?

### Authenticity

정보가 검증된 것이고 신뢰할 수 있는 것인가?

### Accountability

어떤 개인의 위반 행위를 추적할 수 있어야하며 개인은 위반 행위에 대해 책임을 진다.

### Fundamental Security Design Principle

- As simple and small as possible
    - Challenges: Constant demand for new features
- Fail-safe default: default authorization is no
- Every access must be checked against the access control mechanism
- The design of a security mechanism should be open
- Separation of privilege
- Least privilege
- Minimize functions shared by different users
- Usuable Security: Make it easy to use
- Isolation: Access isolation(public resource / critical resource), Entity(접근하는 사람) isolation
- Encapsulation
- Modularity
- Layering
- Least astonishment: 사용자들이 덜 놀라게 만들어라?

### Attack Surface

공격 가능한 취약한 곳

### Attack Tree

공격 가능한 곳을 Tree로 나눠 계층화함

## Chapter 2

### Encryption

Plain text &rarr; Encrypted text **Transformation**
One bit or byte pattern transformation

### Symmetric Key Crypography

공유된 하나의 Secret Key로 Encryption과 Decryption 다 한다.

#### Two principles

- Subsitution
- Permutation

#### Two Attack Approaches

- Cryptanalysis
- Brute-force attack

#### Secret algorithm

Secret Key를 이용한 Encryption & Decryption Algorithm

- Commercial: Published
- Military: Hidden

#### Classical Ciphers

- Substitution
    - Caesar: 알파벳 순서 shift &rarr; 모든 경우의 수 사용(대문자로 한정 26가지)
    - Monoalphabetic Cipher: Alphabet 랜덤 매핑 &rarr; Frequency of alphabet
    - One-time pad: Alphabet 랜덤 매핑이 매번 바뀜

- Permutation
    - 글자의 순서만 바꿈
    - Rail Fence Cipher: 글자 절반으로 나눠서 두 줄로 만들고 윗줄, 아랫줄 앞에서부터 번갈아가면서 쓰기

- Product Ciphers
    - Substituion과 Permutation methods 여러개 섞기

#### Cyrptanalysis Scheme

- Ciphertext only:
    - Bruteforce, 많은 양의 Ciphertext 필요
- Known plaintext:
    - time, spy's name 등을 monoalphabetic cipher로 시도
- Chosen plaintext
    - 시스템에는 접근할 수 있으나, key가 없어서 decryption 불가
    - 시스템에 접근해서 encrypted 만들 수 있기 때문에, 차이가 조금 나는 text 이용

#### Timing Attack

Encrypting / Decrypting 과정을 보면서 Power나 Period 차이를 보면서 연산 추측

#### Type of Security

- Unconditional Security  
Computing power이 무한히 제공되어도 해킹 불가
- Computational Security  
해킹해서 얻을 수 있는 효용 < 해킹 비용

#### Modern Methods: Block Encryption Algorithm

고정 크기의 데이터 블록에서 작동하는 알고리즘

- DES(Data Encryption Standard)
- AES(Advanced Encryption Standard)

그냥 한 bit/byte 씩 Stream으로 읽으면서 Encryption 하는 방식도 있다.

#### Feistel Cipher Structure

Product Cipher에 기반한다.

##### Substitution - Permutation Cipher

- S - P Network
    - Substitution(S-box)
    - Permutation(P-box)
- Confusion: Ciphertext와 Key의 관계를 최대한 복잡하게 만들자
- Diffusion: Plaintext의 확률적 구조를 없애기 &rarr; 한 bit만 바뀌어도 크게 encrypted text가 크게 변함
    - Avalanche Effect

1. Block 을 절반으로 나눔 (L, R)
2. R은 다음 L이 되고 L XOR F(K, R) (Substitution)이 다음 R이 됨 (Permutation)

Decryption 시에는 Encryption 시에 사용했던 Key의 순서를 반대로 해서 입력하면 된다.

#### DES

1. 64-bit Input에 대해 Permutation
2. Fiestel Cipher Structure가 16rounds 진행된다.
    1. Per-Round Key Generation  
        - Initial Key(56 bits) 생성 후 각 절반을 1, 2, 9, 16 round 에서는 single shift, 나머지는 2 bit shift 
        - 이후 각각 절반은 다음 Key generation의 Input이 된다.
        - 해당 Round Key는 Permutation with Discard &rarr; 48bit Key 생성

    2. F(K, R): Mangler Function
        - 4 bits * 8개 조각 만들기
        - 32 bits &rarr; 48bit expansion (6 bits * 8개)
        - Sub key와 XOR
        - Substitution (I1, I6(2bit 2진수)는 Row, I2, I3, I4, I5(4bit 2진수)는 Column )
            - Table 내 index로 찾은 숫자를 또 6 bit 2진수 만들기
        - Permutation

##### 변형

- ECB: 각 Block이 Independently encrypted & decrypted
- CBC(Cipher Block Chaining): 이전 결과와 다음 Input을 XOR 한다.
- CFB(Cipher Feedback): 이전 Ciphertext를 Input으로 돌리고 결과물을 다음 Plaintext와 XOR한 것이 다음 Input이 된다.
- OFB(Output Feedback): 이전 DES Ouput이 다음 Input이 되며, 현재 Plaintext와 XOR 한 것이 Cipher text가 된다. 

##### 특징

DES는 강력한 Avalanche Effect를 가진다.

##### 발전 버전

- Triple-DES  
DES 세개 붙이기
- AES

## Chapter 3

### Public Key Cryptography

- Symmetric Key면 분실 시 책임소지 애매함 (Accountability 위배)
- One private key and Public Key pair
- Public Key isn't more secure
    - Security는 key length & computational work에 dependency가 있음
- General-purpose Technique 가 아니다.
    - Computational efficiency를 생각하면 Symetric
- Key distribution isn't always easy
    - 아니다. Reliable distribution agent and procedure is needed

#### Usage

1. Confidentiality: Plain text를 Public Key로 Encrypt 후 Private Key로 Decrypt
2. Integrity: Digest를 Private Key로 Encrypt 후 Public Key로 Decrypt

#### RSA

##### Diffie-Hellman Key Agreement

두 사람 간에 Private key를 공유하면 Secret Key 만들 수 있음

##### Assumption / Theoretical Basis

큰 수를 두개의 소수의 곱으로 나타내기 어렵다.

##### Preparation

1. Variable Key length
2. Variable Block Size
    - Plaintext는 key보다 크기가 작아야한다.
    - Ciphertext는 key와 크기가 같다.

##### Key generation

1. 256bit 이상인 소수 p, q를 정하기
2. n = p * q
3. (p-1)(q-1)와 relative prime(서로소)인 e 찾기
    - pub = \<e, n\>
4. $e * d = 1 mod \phi(n)$를 만족하는 d 찾기
    - priv = \<d, n\>

##### Encyption

$c = m^{e}modn$

##### Decryption

$m = c^{d}modn$

##### Signature

$s = m^{d}modn$

##### Verification

$m = s^{e}modn$

##### DES vs. RSA

DES가 훨씬 빠름

#### Elliptic Curve

RSA 보다 짧은 Private Key 가능 larr; RSA는 Key의 bit수가 복잡도를 정하지만, Elliptic Curve는 size of elliptic curve가 복잡도를 정한다.

## Chapter 4

### Hash Function이 필요한 이유

- Digest가 필요할 때
- 원문 복원이 필요없을 때
- key가 필요없을 때
- 충돌 검사할 때

### Hash Function 특징

- Input 사이즈 상관 없음
- Output 사이즈 고정
- 어떤 Input 이든, 계산속도가 빠름
- 단방향 rarr; 복원 불가
- Weak collision resistant: 같은 output에 대해 input 추정이 불가능해야한다.
- Strong collision resistant: 같은 output을 가질 input 추정이 불가능해야한다.
    - m bit output에 대해, $2^{m/2}$개를 추정해야한다.
    - 128 bit 이상이어야한다.

### General Structure of Secure Hash Code

1. L개의 Hash 함수를 지나면서 Input을 L개의 Block으로 나눠서 하나씩 넣어준다.
2. initial key외에는 현재 Hash 함수의 key는 이전 Hash 함수의 output이다.

### MD5

1. Message뒤에 Padding과 Message Length를 넣어서 L * 512 bits로 만든다. (Padding Twist: Padding 방식을 바꾸기)
2. Key로 32bit * 4개 (A|B|C|D) 만들기
3. 4 round 16 steps, 각 round마다 다른 함수 사용

### SHA-1

#### 특징

- Input의 길이는 $< 2^{64}$
- Message는 512 bit block size로 계산 됨
- Digest는 160bits

### SHA-1 vs. MD5

- SHA-1의 Bruteforce가 더 힘들다. (160bits vs. 128bits)
- 대신 더 느리다.

### Public-Key는 믿을 수 있어?

Certificate Authority(CA)에서 Public Key에 대한 보증을 해준다.

## Chapter 5

### Authentication

- Access Control와 User Accountability를 위해 필요
- 2 steps
    - Identification Step: Security System를 사용할 수 있는 사람인가?
    - Verification Step: Entitiy와 identifier binding을 입증하는 인증 정보를 제공 또는 생성
- Participating Entities
    - Registration Authority(RA): 인증 등록 기관
    - Credential Service Provider(CSP): 인증 토큰 등록 및 발행 기관
    - Relying Party(RP): Secured Software Application에 접속할 수 있게 해줌

#### Means of Authentication

- Something you know: Password
- Something you have: physical key rarr; token
- Something you are(static biometics): Fingerprint
- Something you do(dynamic biometrics): Voice pattern

#### Risk Assessment

- Lv1. User ID & Password
- Lv2. LV1. + 위 Means 중 하나
- Lv3. 1개 이상의 factor of authentication
- Lv4. 여러개의 factor of authentication + in-person registration

#### Password-based Authentication

ID와 ID의 Authentication을 담당하는 PW를 제공

- ID로 system 접근 가능 여부 판단
- ID로 privileges 판단
- ID는 DAC(Discretionary Access Control)에서 사용

#### Unix password system

- Hash function: 25 rounds DES
    - Key에 Salt를 추가
- Password file은 공개적으로 읽을 수 있음
- Dictionary Attack 가능
- Salt를 추가해서 Dictionary Attack 어렵게 만듦

#### Token-based Authentication

Memory Cards, Smart Cards 등

#### Biometric Authentication

- Scanned Information 에서 Error가 있을 수도 있음
- Threshold를 낮출수록 더 많이 allow 하지만, False Match Rate 증가

#### Remote User Authentication

네트워크 상 원격으로 인증할 때 Challenge-Response 절차 추가

##### Challenge-Response

Nounce, Public Key cryptography

#### Entropy

Randomness or diversity of a data-generating function

#### Authentication in Metaverse

- Identity theft
- Impersonation attack: Generate Digital Replica via stealing data
- Avatar authentication: 내가 마주하는 아바타 믿을 수 있어?
- Interoperable authentication: Cross-platform identity authentication

## Chapter 6

### Access Control

데이터에 authorized entity만 접근 허용하게 하자

#### Access Control Context

1. User가 Authentication Function을 통해서 Authenticate하기
2. Access control function을 통해서 권한 찾기
3. 권한에 맞게 System Resource 사용

#### 용어

- Subject: an entity capable of accessing objects
    - Owner: Creater of a resource or a system administrator
    - Group: A named group of users and a membership in the group 접근 가능한 사람
    - World: Owner, Group 아닌 모두 다
- Object: resource
- Access Right
    - Read
    - Write
    - Execute
    - Delete
    - Create
    - Search

#### DAC(Discretionary Access Control)

Owner 혹은 Group에서 다른 entity의 access right를 자유롭게 변경시킬 수 있음
&rarr; root 권한 탈취 시 모든 resource에 대한 access right 가질 수 있음

##### Implementation

- Access Control Matrix: row(Subjects), col(Objects)로 구성되며, 각 user별 file의 access right확인 가능
- Access Control Lists: 각 File 별로 Access Right이 있는 User이 Linked list로 연결됨
- Capability Lists: 각 User 별로 Access Right이 있는 file이 linked list로 연결됨

read\* 처럼 되어있으면 권한을 다른 사람에게 부여할 수 있음

##### Unix/Linux

user(/etc/password)와 group(/etc/group) 외에 모든 것은 file이다.  
10 bit로 Access Right 나눔

|directory|user|group|other|
|:-------:|:--:|:---:|:-----:|
|d|rwx|rwx|rwx|rwx|

- Three Additional Bits
    - SetUID: user에 대해 파일 실행동안만 Root 권한 부여
    - SetGID: group애 대해 파일 실행동암나 Root 권한 부여
    - Sticky Bit: 소유자만 파일 삭제 권한 있음

##### Problem of DAC

- Trojan Horse
    - 권한이 없는 Object O를 복사하고 권한이 있는 사람에게 쓰기 권한을 줌
    - 해당 파일을 실행하게 끔 하기
    - 권한 없는 사람도 복사된 파일을 통해서 권한 있는 파일을 볼 수 있게 됨

##### Solution to DAC

Lattice Model: 더 높은 권한을 가진 사람에게는 더 낮은 레벨의 데이터에 대한 접근이 가능하도록 하자

### MAC(Mandatory Access Control)

- 다음 두가지에 기반한다
    - Comparing Security Labels: How sensitive or critical system resources are
    - Security Clearances: Eligible to access certain resources
- 권한 있는 entity가 다른 entity에게 권한을 줄 수 없다.
- 오직 system만 권한을 줄 수 있다.

### RBAC(Role-Based Access Control)

- 각 entity는 여러 role을 가질 수 있다.
- 각 role 별로 access control 부여
- Variation
    - RBAC0: 최소한의 기능
    - RBAC1: RBAC0 + 계층구조(상속 가능)
    - RBAC2: RBAC0 + RBAC 시스템의 구성 요소를 수정할 수 잇는 방법 및 제약 조건 추가

### ABAC(Attribute-Based Access Control)

Role을 넘어서서 환경 등 다양한 요소들을 포함한 Attribute 기반

#### Identity Management

attribute에 대해 digital identity 부여, 개인과 연결

#### Credential Management

identity(혹은 attribute)와 subscriber(resource사용하고자 하는 entity)의 token과 연결

#### Identity Federation

다른 조직에서 발행된 identity와 credential를 신뢰할지 결정

##### Trust Framework

Identity Exchange

### Metaverse Access Control

#### Threats

VSP(Virtual Service Provider)가 malicious하다면?

#### Countermeasures

Fine-grained access control
and usage audit for wearables and UGCs(User Generated Content)

    - ABAC variant로 Fine-grained access control 제공

## Chapter 7

### SQL Intection

#### In band attacks

- Tautology: Conditional Statement를 always true로 만들기
- End-of-line commment: Query문 추가 후에 뒤에 end of line처리 해서 뒷부분 실행x
- Piggybacked queries: 원래 query뒤에 추가 query 넣기

### Database Access Control

DBMS에 접근 및 데이터 변형 권한이 나눠져있음

### Inferential Attack

직접 정보를 취득할 수는 없으나 쿼리를 날려서 간접적으로 추측  
잘못된 쿼리를 날려서 구조 및 타입 추측 가능

### Out-band Attack

Information retrieval은 제한되지만, Outbound connectivity 보안이 약하다면 가능

### DB RBAC

Role을 부여하여 Access Control 관리

### Statistical Databases

통계 데이터를 통한 inference attack

### Countermeasures from Inference Attack

#### Perturbation

- Add noise
- Data swapping
- must minimize loss of accuracy in results

#### DB Encryption

- Entire DB
- Individual Field
- records(rows) or columns(attributes)
    - query시에 index 접근

### Cloud computing

#### Essential Characteristics

- Broad network access: 다양한 기기를 통해서 다양한 곳에서 접근
- Rapid elasticity: 네트워크 사용량이 날마다 격차가 많이 남
- Measured service: 쓴만큼 돈이 나옴
- Demand service: 소비자에게 고정적으로 제공되는 부분이 없이 쓰는 만큼 쓰는 것이다.
- Resource pooling
    - Provider는 Multi-tenant model을 이용해 유기적으로 resource를 assign & reassign
    - Consumer는 resource의 physical location을 몰라도 됨

#### SaaS

Application software의 형식으로 제공되며, 다양한 플랫폼에서 접속가능한 interface 제공

#### PaaS

Customer가 본인의 프로그램을 올려서 실행할 수 있는 형태이다.  
PaaS에서는 유용한 block/tools 제공

#### IaaS

Client가 underlying cloud infrastructure에 직접 접근해서 개발할 수 있도록 해줌  
VM, OS, API 등을 제공한다.  
AWS EC2, Azure 등이 해당

#### Deployment 방법

- Public
- Private
- Commnuity
- Hybrid

#### Cloud Service Participants

- Cloud customer: Cloud Provider의 Service의 고객
- Cloud provider(CP): Cloud Service 제공자
- Cloud auditor: security 등 source에 대한 평가를 내리는 자
- Cloud broker: use, performance 등을 관리하는 자
- Cloud carrier: Connectivity, service transport를 위해 중간에 있는 자

#### Role of CP

- SaaS: software 관리
- PaaS: platform을 위한 computing infrastructure 관리(middleware, database 등)
- IaaS: physical computing resources 관리

#### Security Risks

##### Abuse use of cloud computing

- register이 쉽고, free-trial이 제공됨
- hacker들이 해킹위해 쉽게 접근 가능
- CP가 모든 보안을 담당하기 부담

###### Countermeasures

- Registration을 어렵게 만들자
- Traffic등 서비스 monitoring

##### Insecure interfaces of API

API의 보안은 Secure해야한다.

###### Countermeasures

- API의 security 분석
- Strong authentication과 access control 보장
- API간 dependency 분석

##### Malicious insiders

다른 Client 중 Malicious 이용자가 있을 수도 있다.

###### Countermeasures(by client)

- Supplier에 대해 종합적으로 평가

##### Shared technology issues

IaaS 서비스의 경우 shared infrastructure 존재  
Multi-tenant architecture로 디자인 안 되어있을 수도 있음

###### Countermeasures

- CP는 secure하게 설계하고 서비스 배포해야함
- Unauthorized activies 모니터링
- Strong authentication & access control 촉진

##### Data loss or leakage

Cloud storage가 유일한 backup storage인데 Loss 된다면..?

###### Countermeasures

- Implement strong API access control
- 데이터 이동 시 Encrypt and protect integrity
- 디자인, runtime 단계에서 data protection 분석

##### Account or service hijacking

credential이 stolen된다면..?

###### Countermeasures

- User간 credential sharing 막기
- multi-factory authentication

## Chapter 8

### Formal Security Model

모든 Security requirements과 Design Specification을 만족하는 디자인을 만들어보자  
그러기 위해서 기준이 되는 Fromal model of computer security를 만들자
Confidentiality Policy를 만족하는 모델로 Multi-level security model이 알려져 있다.

### BLP

#### Terminology

- L(s): Levels consit of security clearance
- L(o): Levels consist of security classification
- ss-property: subject은 security level이 본인 이하인 object만 읽을 수 있다.
- \*-property: subjectsms 본인 이상인 object만 쓸 수 있다.
- Levels
    - Top Secret
    - Secret
    - Confidential
    - Unclassified

#### Description

- Based on MAC
- (b, M, f, H)
    - b: Current access set (subjets, objects, access-mode)
    - M: Access Matrix
    - f: Level Function
    - H: Sec level 에 따른 directed tree
- BLP properties
    - ss-property: 동일
    - \*-property:
        - append는 본인 이상인 경우 가능
        - write는 본인과 동일 level만 가능
    - ds-property: ($S_{i}$,$O_{j}$, $A_{x}$), $A_{x} \in M[S_{i}, O_{j}]$
        - 본인이 소유한 파일 이외에는 permission이 있어야한다.
- Security Classification에 Category 추가 가능
    - (A, C) dominates (A\`, C\`) if security level of A\`<=A and C\`<=C

#### Limitations

- Confidentiality and Integrity가 하나의 시스템에 공존할 수 없다.
- 공유파일의 경우 \*-property를 가용할 수 없다.
    - (untrusted) low classified executable data가 high clearance subject에 의해 실행되면 BLP 모델이 파괴된다.


### Biba Integrity Model

Integrity: 권한이 없는 사람에게 data가 변형되거나 접근하는 것이 불가능하다는 특성  

#### Strict integrity policy

- Simple integrity: I(s) >= I(o) only if 수정 가능
- Integrity confinement: I(s) <= I(o) only if 읽기 가능
- Invocation property: I(s1) >= I(s2) only if 통신을 위해 호출 가능

### Clark-Wilson Integrity Model

#### Concepts

- Well-formed transactions: 데이터의 무결성을 보존, 보장하는 제약 아래 조작
- Separation of Duty: Transaction 생성은 가능하나 실행은 불가능

#### Certified and Enforcement Rules

는 PPT 참고 ^^ (31, 32쪽)

### The Chinese Wall Model

- Not a Multilevel secure model
- History of a subject's access determines access control

#### Terminology

- Subject: Entity
- Object: Individual data items which is about a corporation
- dataset: all objects concerning one corp
- CI class: datasets whose corp are in competition

#### Access rule

한번 접근한 데이터에 대한 CI는 접근 불가

- Simple security rule(read)  
    - O가 S가 이미 접근한 데이터와 같은 DS에 있거나
    - O의 CI에 접근한적이 없을 때 읽을 수 있다.
- \*-property (write)
    - O를 S가 읽을 수 있고
    - S가 읽을 수 있는 모든 Objects가 O와 같은 DS에 있을 때 쓸 수 있다.

#### Information Flow

- Unsanitized(기밀이 남아 있는 문서)  
    CD내에 남아있어야한다.
- Sanitized  
    자유롭게 돌아다닐 수 있다.

#### CW와 Bell-LaPadula 비교

- CW는 access history에 기반, BLP는 history-less
- BLP는 CW의 state를 확인할 수 있지만 추적 불가  
    &rarr; access이 허용될 때마다 BLP 업데이트 해야 한다.

#### Trusted Systems

- Trusted system: Given set of attributes를 State degree of assurance 지키는다고 알려진 시스템
- Trustworthiness: 시스템이 신뢰할 만하다는 보증
- Trusted computer system: 어떤 범위의 민감함 또는 분류된 정보의 동시적 처리를 위해 사용이 허용된 하드웨어와 소프트웨어의 보증 조치를 충분하게 가진 시스템
- TCB: 특정 Policy를 시행하는 시스템의 작은 부분으로, tampering과 circumvention을 이겨내고 systematically 분석할 수 있도록 작아야한다.

### Reference Monitors

#### Properties

- Complete mediation: 모든 접근에 대해 Security Rules 적용
- Isolation: RM & DB는 Unauthorized access로부터 보호된다.
- Verifiability: RM의 올바름이 증명되야한다.
- No readup, No write down 따름

#### Trojan Horse Defense

- Bob이 Alice보다 Security level이 높음
- Bob이 소유한 파일에는 credential information 저장되어있음
- Alice는 파일을 생성하여 본인은 rw 부여, Bob에게는 w 부여 후 Back-pocket file와 연결
- Bob이 Alice의 파일을 실행하여 Credential information 뺏으려고 함
- 하지만, No-write-down 때문에 막힘

### Multi-level Security

- 시스템에 접근 권한이 있는 일부 사용자가 시스템에 의해 다뤄지는 일부 데이터의 security clearance와 need-to-know가 필요없을 때, 두개 이상의 security levels of information이 동시에 다뤄지도록 허용한다.
- OS에 의존하여 clearance과 classification level 기반하여 user와 classified matrial 분리

#### usage

- RBAC는 BLP MLS rules를 구현할 수 있다.
- MLS in Database Security

### TPM

#### Services

- Authenticated Boot Service  
부팅 시 각 부분이 승인된 버전임을 알려줌
- Certification Service
TPM의 private key를 이용해 configuration information의 description에 서명 가능
- Encryption Service  
해당 TPM에서만 Decrypt 가능한 secret key 보유

## Chapter 9

### Why OS Security?

- authentication, access control, resource management 등의 보안 기능 제공
- planning, installation, configuration, pdate, maintenance등의 hardening process 필요

### Hardening Measures

1. 허용된 응용프로그램만 실행
2. third-party 응용프로그램과 OS 취약점 패치
3. 관리자 권한을 필요로 하는 사용자 제한
4. 다계층 방식의 방어 시스템 구축

### System Security Planning

적절한 인원을 훌련시켜서 OS 설치 및 관리할 수 있도록 계획 세우기  
OS 위의 프로그램 데이터 등의 보안 요구사항 결정

### OS Hardening

- OS 설치 및 패치
- 시스템의 보안 요구 사하을 충족할 수 있도록 설정하기
- 추가적인 security control(백신 등) 설치 및 설정
- 불필요한 서비스 제거
- Configure Users and Privileges
- Configure Resource Controls
- 보안 요구사항이 잘 지켜졌는지 테ㅍ스트해보기

### Application Configuration

Application을 위한 적절한 Data Storage 만들고 지정 등

### Security Maintenance

- 지속적으로 Log 분석
- backup (planning 단계에서 결정)
- 보안 위협으로 부터 복구
- 지속적인 테스트
- 적절한 소프트웨어를 사용하여 보안 유지

### Linux/Unix Security

- Chroot jail  
어떤 프로세스가 실행될 때, root directory의 위치를 실제와 다른 곳으로 변경  
해당 위치보다 상위 directory는 접근 불가

































