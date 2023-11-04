# RDP

### 먼저, 전체적인 설명에 대한 내용이 필요한 경우,
### 혹은 코드에 예외가 발생하여 해결해야 하는 경우,
### README.md에 추가해주세요.

### 레포트 관련해서 적어야 하는 경우는, 
### README.txt에 추가해주세요.

- RDP class: Recursive Descent Parsing을 수행
  - 토큰 종류를 심볼 종류를 표현하는 열거형 TOKEN_TYPE으로 정의
  - 생성자와 소멸자 사용해 파일을 열고 닫음
- addToken(): 토큰을 토큰 목록에 추가
  - _tokens 벡터에 현재 tokenString 값을 추가
- _tokens 벡터: 파싱된 토큰들을 저장
- getChar(): 다음 문자를 읽어옴
  - _ch: 현재 파싱 중인 문자
- isSpace(), isOperator(), isSpecial(): 문자의 공백 여부, 연산자 여부, 특수 문자 여부 판별
- msgError(), msgWarning(): 오류, 경고 메시지 생성 및 결과에 메시지 추가
- printStatement(): 파싱된 문장 출력
  - _tokens 벡터를 순회하며 토큰들 출력
  - _ID, _CONST, _OP 값을 출력해 각각의 개수 표시
  - _result에 오류/경고 메시지가 있으면 출력
- printSymbolTable(): 심볼 테이블 출력
  - _symTable 맵을 순회하며 변수 이름과 값을 출력
- factor(): <factor>를 처리
  - nextToken == 식별자: 변수를 처리하고 _symTable에 해당 변수 추가
  - nextToken == 상수: 상수 처리
  - nextToken == ‘(‘: 괄호 안의 표현식 계산
  - else: 오류 처리
- term(): <term>을 처리
  - factor()를 호출해서 term을 계산하고 ‘*’ 또는 ‘/’을 처리
- expression(): <expression>을 처리
  - term()을 호출해서 expression을 계산하고 ‘+’ 또는 ‘-’을 처리
- statement(): 각 문장을 처리
  - nextToken을 검사해서 변수 할당문을 처리하고 _symTable을 업데이트
  - _result에 오류 메시지 추가
- statements(): 문장 여러 개를 처리
  - lexical()을 호출해서 다음 토큰을 읽고 statement()를 호출해서 문장을 처리
- lexical(): 토큰을 읽고 종류를 결정
  - 문자를 인식하고 해당하는 nextToken값을 설정
  - 오류 처리도 수행
- main(): 프로그램 진입점
  - 입력 파일 열고 파싱 작업 수행
