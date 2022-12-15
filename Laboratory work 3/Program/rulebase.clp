(defrule data-input
  (initial-fact)
=>
  ; ���� ��������
  (printout t crlf "������� ���� ������� : ")
  (bind ?years (read))
  (if (or (< ?years 5) (> ?years 100))
      then (printout t crlf "������ �����!")
      else (assert (years ?years)))
  
  ; ���� ���������� � �����
  (printout t "�������������� ���� (1-������, 2-��������, 3-�������, 4-�����, 5-����������): ")
  (bind ?genre (read))
  (assert (genre ?genre))
  
  ; ���� ���������� � ���� ����
  (printout t "��� ���� (1-�����, 2-������): ")
  (bind ?typeCinema (read))
  (assert (typeCinema ?typeCinema))
  
  ; ���� ���������� � ���������� ���������
  (printout t "� ��� �������? (1-����, 2-� ��������, 3-� ������): ")
  (bind ?withCompany (read))
  (assert (withCompany ?withCompany))
  
  ; ���� ���������� � �������
  (printout t "���� (1-�����, 2-������): ")
  (bind ?yearsCinema (read))
  (assert (yearsCinema ?yearsCinema))

  ; ���� ���������� � �������������� ������
  (printout t "������ ������������(1-����������, 2-�������, 3-�������): ")
  (bind ?country (read))
  (assert (country ?country)))


; ����� ������ � ���������� ������
(defrule R1
	(years ?years)
	(test (< ?years 12)) 
=>
(assert (age Child)))

(defrule R2
	(years ?years)
	(test (>= ?years 12)) 
=>
(assert (age Teenager)))

(defrule R3
	(years ?years)
	(test (>= ?years 18)) 
=>
(assert (age Adult)))

; ������ ����������� ������ ��� ���������� ������� ������������� ����
; ��������� ������ ����� �����
(defrule R4
	(age Child)
	(or(genre 1)(genre 2)(genre 4))
	(or(typeCinema 1)(typeCinema 2))
	(or(withCompany 1)(withCompany 2)(withCompany 3))
	(or(yearsCinema 1)(yearsCinema 2))
	(or(country 1)(country 2)(country 3))
=>
;����� ��������� � ������� � ���������� ������� ���������� ������� 
(printout t "������������� � ��������� >> ���������� � ���� ������" crlf)
(assert (recommended "Yes"))
)

(defrule R5
	(age Child)
	(genre 3)
	(or(typeCinema 1)(typeCinema 2))
	(or(withCompany 1)(withCompany 2))
	(or(yearsCinema 1)(yearsCinema 2))
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> �����-���" crlf)
(assert (recommended "Yes"))
)

(defrule R6
	(age Child)
	(genre 3)
	(or(typeCinema 1)(typeCinema 2))
	(withCompany 3)
	(or(yearsCinema 1)(yearsCinema 2))
	(or(country 2)(country 3))
=>
(printout t "������������� � ��������� >> ������" crlf)
(assert (recommended "Yes"))
)

(defrule R7
	(age Child)
	(genre 5)
	(or(typeCinema 1)(typeCinema 2))
	(or(withCompany 1)(withCompany 2)(withCompany 3))
	(or(yearsCinema 1)(yearsCinema 2))
	(or(country 2)(country 3))
=>
(printout t "������������� � ��������� >> ��� � �����" crlf)
(assert (recommended "Yes"))
)

;������������ �������
(defrule R8
	(age Teenager)
	(genre 1)
	(typeCinema 1)
	(withCompany 1)
	(yearsCinema 1)
	(or(country 1)(country 3))
=> 
(printout t "������������� � ��������� >> ������� �657" crlf)
(assert (recommended "Yes"))
)
(defrule R9
	(age Teenager)
	(or(genre 1)(genre 2))
	(typeCinema 1)
	(or(withCompany 1)(withCompany 2)(withCompany 3))
	(yearsCinema 2)
	(country 2)
=>
(printout t "������������� � ��������� >> ���� (1 � 2 �����)" crlf)
(assert (recommended "Yes"))
)
(defrule R10
	(age Teenager)
	(genre 3)
	(typeCinema 1)
	(or(withCompany 1)(withCompany 2)(withCompany 3))
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> �� �������� ������" crlf)
(assert (recommended "Yes"))
)
(defrule R11
	(age Teenager)
	(genre 3)
	(typeCinema 1)
	(or(withCompany 1)(withCompany 2)(withCompany 3))
	(yearsCinema 2)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> �����" crlf)
(assert (recommended "Yes"))
)
(defrule R12
	(age Teenager)
	(genre 3)
	(typeCinema 1)
	(or(withCompany 1)(withCompany 2)(withCompany 3))
	(yearsCinema 2)
	(country 2)
=>
(printout t "������������� � ��������� >> �������� �" crlf)
(assert (recommended "Yes"))
)
(defrule R13
	(age Teenager)
	(genre 4)
	(typeCinema 1)
	(or(withCompany 1)(withCompany 2))
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ����� (1 � 2 �����)" crlf)
(assert (recommended "Yes"))
)
(defrule R14
	(age Teenager)
	(genre 4)
	(typeCinema 2)
	(or(withCompany 1)(withCompany 2))
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ������� ��������" crlf)
(assert (recommended "Yes"))
)
(defrule R15
	(age Teenager)
	(genre 4)
	(typeCinema 1)
	(withCompany 2)
	(yearsCinema 2)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ���� (��� �����)" crlf)
(assert (recommended "Yes"))
)
(defrule R16
	(age Teenager)
	(genre 5)
	(typeCinema 1)
	(or(withCompany 1)(withCompany 2)(withCompany 3))
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ������" crlf)
(assert (recommended "Yes"))
)
(defrule R17
	(age Teenager)
	(genre 5)
	(typeCinema 2)
	(withCompany 3)
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ���������� � �������" crlf)
(assert (recommended "Yes"))
)
(defrule R18
	(age Teenager)
	(or(genre 2)(genre 4)(genre 5))
	(typeCinema 2)
	(withCompany 1)
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ������������" crlf)
(assert (recommended "Yes"))
)
(defrule R19
	(age Teenager)
	(or(genre 1)(genre 2)(genre 3)(genre 5))
	(typeCinema 2)
	(withCompany 2)
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ���� ���������" crlf)
(assert (recommended "Yes"))
)
(defrule R20
	(age Teenager)
	(or(genre 2)(genre 5))
	(typeCinema 1)
	(or(withCompany 2)(withCompany 3))
	(yearsCinema 2)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ����� ������ (��� �����)" crlf)
(assert (recommended "Yes"))
)

;����� ������� ���������
(defrule R21
	(age Adult)
	(genre 1)
	(typeCinema 1)
	(withCompany 1)
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ���������� 2: ������ ����" crlf)
(assert (recommended "Yes"))
)
(defrule R22
	(age Adult)
	(genre 2)
	(typeCinema 1)
	(withCompany 1)
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ������ �������" crlf)
(assert (recommended "Yes"))
)
(defrule R23
	(age Adult)
	(or(genre 3)(genre 4))
	(typeCinema 1)
	(withCompany 1)
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ������������ �����" crlf)
(assert (recommended "Yes"))
)
(defrule R24
	(age Adult)
	(genre 4)
	(typeCinema 1)
	(or(withCompany 1)(withCompany 2))
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> �������� �����" crlf)
(assert (recommended "Yes"))
)
(defrule R25
	(age Adult)
	(genre 5)
	(typeCinema 1)
	(or(withCompany 1)(withCompany 2))
	(yearsCinema 2)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ������������ (��� �����)" crlf)
(assert (recommended "Yes"))
)
(defrule R26
	(age Adult)
	(genre 1)
	(typeCinema 2)
	(or(withCompany 1)(withCompany 2))
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ��������" crlf)
(assert (recommended "Yes"))
)
(defrule R27
	(age Adult)
	(genre 2)
	(typeCinema 2)
	(withCompany 3)
	(yearsCinema 2)
	(country 2)
=>
(printout t "������������� � ��������� >> ��������� 46" crlf)
(assert (recommended "Yes"))
)
(defrule R28
	(age Adult)
	(or(genre 3)(genre 4)(genre 5))
	(typeCinema 2)
	(or(withCompany 2)(withCompany 3))
	(yearsCinema 1)
	(country 2)
=>
(printout t "������������� � ��������� >> ���� �� ���������" crlf)
(assert (recommended "Yes"))
)
(defrule R29
	(age Adult)
	(or(genre 2)(genre 3))
	(typeCinema 1)
	(or(withCompany 1)(withCompany 2)(withCompany 3))
	(yearsCinema 2)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ���� ���� (��� ������)" crlf)
(assert (recommended "Yes"))
)
(defrule R30
	(age Adult)
	(or(genre 1)(genre 3)(genre 5))
	(typeCinema 1)
	(withCompany 3)
	(yearsCinema 1)
	(country 2)
=>
(printout t "������������� � ��������� >> ����� ����: ������ ������" crlf)
(assert (recommended "Yes"))
)
(defrule R31
	(age Adult)
	(or(genre 2)(genre 3))
	(typeCinema 1)
	(withCompany 3)
	(yearsCinema 2)
	(country 2)
=>
(printout t "������������� � ��������� >> ������������ �����" crlf)
(assert (recommended "Yes"))
)
(defrule R32
	(age Adult)
	(or(genre 1)(genre 2)(genre 3))
	(typeCinema 1)
	(withCompany 3)
	(yearsCinema 2)
	(country 2)
=>
(printout t "������������� � ��������� >> ������������� ����" crlf)
(assert (recommended "Yes"))
)
(defrule R33
	(age Adult)
	(genre 2)
	(typeCinema 2)
	(withCompany 3)
	(yearsCinema 2)
	(or(country 1)(country 3))
=>
(printout t "������������� � ��������� >> ������� ����" crlf)
(assert (recommended "Yes"))
)
(defrule R34
	(age Adult)
	(genre 1)
	(typeCinema 2)
	(withCompany 1)
	(yearsCinema 2)
	(or(country 2)(country 3))
=>
(printout t "������������� � ��������� >> 9 ����" crlf)
(assert (recommended "Yes"))
)
(defrule R35
	(age Teenager)
	(genre 3)
	(typeCinema 2)
	(withCompany 1)
	(yearsCinema 1)
	(or(country 2)(country 3))
=> 
(printout t "������������� � ��������� >> ���� (��� �����)" crlf)
(assert (recommended "Yes"))
)
(defrule R36
	(age Teenager)
	(genre 3)
	(typeCinema 1)
	(withCompany 1)
	(yearsCinema 2)
	(or(country 2)(country 3))
=> 
(printout t "������������� � ��������� >> ������ � ������" crlf)
(assert (recommended "Yes"))
)