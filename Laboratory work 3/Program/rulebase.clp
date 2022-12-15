(defrule data-input
  (initial-fact)
=>
  ; Ввод возраста
  (printout t crlf "Введите свой возраст : ")
  (bind ?years (read))
  (if (or (< ?years 5) (> ?years 100))
      then (printout t crlf "Ошибка ввода!")
      else (assert (years ?years)))
  
  ; Ввод информации о жанре
  (printout t "Предпочитаемый жанр (1-боевик, 2-детектив, 3-комедия, 4-ужасы, 5-фантастика): ")
  (bind ?genre (read))
  (assert (genre ?genre))
  
  ; Ввод информации о типе кино
  (printout t "Тип кино (1-фильм, 2-сериал): ")
  (bind ?typeCinema (read))
  (assert (typeCinema ?typeCinema))
  
  ; Ввод информации о совместном просмотре
  (printout t "С кем смотрим? (1-один, 2-с друзьями, 3-с семьей): ")
  (bind ?withCompany (read))
  (assert (withCompany ?withCompany))
  
  ; Ввод информации о новизне
  (printout t "Годы (1-новые, 2-старые): ")
  (bind ?yearsCinema (read))
  (assert (yearsCinema ?yearsCinema))

  ; Ввод информации о предпочитаемой стране
  (printout t "Страна производства(1-Зарубежный, 2-Русский, 3-Неважно): ")
  (bind ?country (read))
  (assert (country ?country)))


; Вывод фактов о возрастной группе
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

; Начало определения правил для экспертной системы рекоммендации кино
; Структура правил далее схожа
(defrule R4
	(age Child)
	(or(genre 1)(genre 2)(genre 4))
	(or(typeCinema 1)(typeCinema 2))
	(or(withCompany 1)(withCompany 2)(withCompany 3))
	(or(yearsCinema 1)(yearsCinema 2))
	(or(country 1)(country 2)(country 3))
=>
;Вывод сообщения в консоль о результате решение экспертной системы 
(printout t "Рекомендуется к просмотру >> Белоснежка и семь гномов" crlf)
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
(printout t "Рекомендуется к просмотру >> Спанч-Боб" crlf)
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
(printout t "Рекомендуется к просмотру >> Ералаш" crlf)
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
(printout t "Рекомендуется к просмотру >> Кот в шляпе" crlf)
(assert (recommended "Yes"))
)

;Подростковый возраст
(defrule R8
	(age Teenager)
	(genre 1)
	(typeCinema 1)
	(withCompany 1)
	(yearsCinema 1)
	(or(country 1)(country 3))
=> 
(printout t "Рекомендуется к просмотру >> Автобус №657" crlf)
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
(printout t "Рекомендуется к просмотру >> Брат (1 и 2 часть)" crlf)
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
(printout t "Рекомендуется к просмотру >> Не смотрите наверх" crlf)
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
(printout t "Рекомендуется к просмотру >> Маска" crlf)
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
(printout t "Рекомендуется к просмотру >> Операция Ы" crlf)
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
(printout t "Рекомендуется к просмотру >> Спуск (1 и 2 часть)" crlf)
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
(printout t "Рекомендуется к просмотру >> Ходячие мертвецы" crlf)
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
(printout t "Рекомендуется к просмотру >> Пила (все части)" crlf)
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
(printout t "Рекомендуется к просмотру >> Аватар" crlf)
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
(printout t "Рекомендуется к просмотру >> Потерянные в космосе" crlf)
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
(printout t "Рекомендуется к просмотру >> Пространство" crlf)
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
(printout t "Рекомендуется к просмотру >> Игра престолов" crlf)
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
(printout t "Рекомендуется к просмотру >> Гарри Поттер (все части)" crlf)
(assert (recommended "Yes"))
)

;Более старшее поколение
(defrule R21
	(age Adult)
	(genre 1)
	(typeCinema 1)
	(withCompany 1)
	(yearsCinema 1)
	(or(country 1)(country 3))
=>
(printout t "Рекомендуется к просмотру >> Терминатор 2: судный день" crlf)
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
(printout t "Рекомендуется к просмотру >> Шестое чувство" crlf)
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
(printout t "Рекомендуется к просмотру >> Американский пирог" crlf)
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
(printout t "Рекомендуется к просмотру >> Молчание ягнят" crlf)
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
(printout t "Рекомендуется к просмотру >> Трансформеры (все части)" crlf)
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
(printout t "Рекомендуется к просмотру >> Каратель" crlf)
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
(printout t "Рекомендуется к просмотру >> Ленинград 46" crlf)
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
(printout t "Рекомендуется к просмотру >> Игра на выживание" crlf)
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
(printout t "Рекомендуется к просмотру >> Один дома (три фильма)" crlf)
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
(printout t "Рекомендуется к просмотру >> Майор Гром: Чумной доктор" crlf)
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
(printout t "Рекомендуется к просмотру >> Джентельмены удачи" crlf)
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
(printout t "Рекомендуется к просмотру >> Бриллиантовая рука" crlf)
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
(printout t "Рекомендуется к просмотру >> Мерзлая зима" crlf)
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
(printout t "Рекомендуется к просмотру >> 9 рота" crlf)
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
(printout t "Рекомендуется к просмотру >> Елки (все части)" crlf)
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
(printout t "Рекомендуется к просмотру >> Любовь и Голуби" crlf)
(assert (recommended "Yes"))
)