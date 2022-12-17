;; ======================================
;; Начальная инициализация входных данных
;; ======================================
(defglobal
	?*ID* = 0
	?*NODES_CREATED* = 1
	?*STEPS_PASSED* = 0

	;; Изначальный граф
	?*init_UpL* = 0
	?*init_UpC* = 4
	?*init_UpR* = 3
	?*init_MidL* = 6
	?*init_MidC* = 2
	?*init_MidR* = 1
	?*init_DownL* = 7
	?*init_DownC* = 5
	?*init_DownR* = 8
	
	;; Конечный путь
	?*result_UpL* = 1
	?*result_UpC* = 2
	?*result_UpR* = 3
	?*result_MidL* = 4
	?*result_MidC* = 0
	?*result_MidR* = 5
	?*result_DownL* = 6
	?*result_DownC* = 7
	?*result_DownR* = 8
	
	;; EF=1:h1 (количество фишек, стоящих не на своем месте); EF=2:h2 (сумма расстояний всех фишек до целевых позиций(манхэттенское расстояние)); DB=1:steps
	?*EvristicFuntion* = 2
	?*DEBUG* = 0
)

;; ======================================
;; Шаблон вершины
;; ======================================
(deftemplate Node
	(slot id(type NUMBER) (default 0))

	(slot UL (type NUMBER))
	(slot UC (type NUMBER))
	(slot UR (type NUMBER))
	(slot ML (type NUMBER))
	(slot MC (type NUMBER))
	(slot MR (type NUMBER))
	(slot DL (type NUMBER))
	(slot DC (type NUMBER))
	(slot DR (type NUMBER))

	(slot parent (type NUMBER))
	(slot depth (type NUMBER))
	(slot f (type NUMBER)) ; значение целевой функции для данной вершины f = depth + h
	(slot status(type NUMBER) (default 0)) ; 0 – не раскрыта, 1 – раскрыта, 2 – соответствует решению
)

;; ======================================
;;  Сумма Манхэттенских расстояний фишек от из целевой позиции (для эвристической функции h2)
;; ======================================
(deffunction manhattanFunc(?v ?i ?j)
	(if (= ?v ?*result_UpL*) then (bind ?i_g 0))
	(if (= ?v ?*result_UpL*) then (bind ?j_g 0))
	
	(if (= ?v ?*result_UpC*) then (bind ?i_g 0))
	(if (= ?v ?*result_UpC*) then (bind ?j_g 1))
	
	(if (= ?v ?*result_UpR*) then (bind ?i_g 0))
	(if (= ?v ?*result_UpR*) then (bind ?j_g 2))
	
	(if (= ?v ?*result_MidL*) then (bind ?i_g 1))
	(if (= ?v ?*result_MidL*) then (bind ?j_g 0))
	
	(if (= ?v ?*result_MidC*) then (bind ?i_g 1))
	(if (= ?v ?*result_MidC*) then (bind ?j_g 1))
	
	(if (= ?v ?*result_MidR*) then (bind ?i_g 1))
	(if (= ?v ?*result_MidR*) then (bind ?j_g 2))
	
	(if (= ?v ?*result_DownL*) then (bind ?i_g 2))
	(if (= ?v ?*result_DownL*) then (bind ?j_g 0))
	
	(if (= ?v ?*result_DownC*) then (bind ?i_g 2))
	(if (= ?v ?*result_DownC*) then (bind ?j_g 1))
	
	(if (= ?v ?*result_DownR*) then (bind ?i_g 2))
	(if (= ?v ?*result_DownR*) then (bind ?j_g 2))
	
	(return (+ (abs (- ?i ?i_g)) (abs (- ?j ?j_g))))
)

;; ======================================
;; Евристика h1
;; ======================================
(deffunction h1(?cur_UL ?cur_UC ?cur_UR
                ?cur_ML ?cur_MC ?cur_MR
                ?cur_DL ?cur_DC ?cur_DR)
	(bind ?a 0)
	(if (not (= ?cur_UL ?*result_UpL*)) then (bind ?a (+ ?a 1)))
	(if (not (= ?cur_UC ?*result_UpC*)) then (bind ?a (+ ?a 1)))
	(if (not (= ?cur_UR ?*result_UpR*)) then (bind ?a (+ ?a 1)))
	(if (not (= ?cur_ML ?*result_MidL*)) then (bind ?a (+ ?a 1)))
	(if (not (= ?cur_MC ?*result_MidC*)) then (bind ?a (+ ?a 1)))
	(if (not (= ?cur_MR ?*result_MidR*)) then (bind ?a (+ ?a 1)))
	(if (not (= ?cur_DL ?*result_DownL*)) then (bind ?a (+ ?a 1)))
	(if (not (= ?cur_DC ?*result_DownC*)) then (bind ?a (+ ?a 1)))
	(if (not (= ?cur_DR ?*result_DownR*)) then (bind ?a (+ ?a 1)))
	
	(return ?a)
)

;; ======================================
;; Евристика h2
;; ======================================
(deffunction h2(?cur_UL ?cur_UC ?cur_UR
                ?cur_ML ?cur_MC ?cur_MR
                ?cur_DL ?cur_DC ?cur_DR)
	(bind ?a 0)
	(bind ?a (+ ?a (manhattanFunc ?cur_UL 0 0)))
	(bind ?a (+ ?a (manhattanFunc ?cur_UC 0 1)))
	(bind ?a (+ ?a (manhattanFunc ?cur_UR 0 2)))
	
	(bind ?a (+ ?a (manhattanFunc ?cur_ML 1 0)))
	(bind ?a (+ ?a (manhattanFunc ?cur_MC 1 1)))
	(bind ?a (+ ?a (manhattanFunc ?cur_MR 1 2)))
	
	(bind ?a (+ ?a (manhattanFunc ?cur_DL 2 0)))
	(bind ?a (+ ?a (manhattanFunc ?cur_DC 2 1)))
	(bind ?a (+ ?a (manhattanFunc ?cur_DR 2 2)))
	
	(return ?a)
)

;; ======================================
;; Функция расчета оценочной стоимости евристики /приоритета (h1 и h2 соответственно)
;; ======================================
(deffunction getF(?depth
                    ?cur_UL ?cur_UC ?cur_UR
                    ?cur_ML ?cur_MC ?cur_MR
                    ?cur_DL ?cur_DC ?cur_DR)
	(bind ?a ?depth)
	(if (= ?*EvristicFuntion* 1) then (bind ?a (+ ?a (h1 ?cur_UL ?cur_UC ?cur_UR ?cur_ML ?cur_MC ?cur_MR ?cur_DL ?cur_DC ?cur_DR))))
	(if (= ?*EvristicFuntion* 2) then (bind ?a (+ ?a (h2 ?cur_UL ?cur_UC ?cur_UR ?cur_ML ?cur_MC ?cur_MR ?cur_DL ?cur_DC ?cur_DR))))
	
	(return ?a)
)

;; ======================================
;; Функция присваивания ID узлу
;; ======================================
(deffunction setID()
	(bind ?*ID* (+ ?*ID* 1))
	
	(return ?*ID*)
)

;; ======================================
;; Инициализация начальной вершины (reset)
;; ======================================
(deffacts initial
	(Node (id (setID))
		(UL ?*init_UpL*) 	(UC ?*init_UpC*) 	(UR ?*init_UpR*) 
        (ML ?*init_MidL*) 	(MC ?*init_MidC*) 	(MR ?*init_MidR*) 
        (DL ?*init_DownL*) 	(DC ?*init_DownC*) 	(DR ?*init_DownR*)
		
        (depth 0) (parent 0) 
        (f (getF 0 ?*init_UpL* ?*init_UpC* ?*init_UpR* ?*init_MidL* ?*init_MidC* ?*init_MidR* ?*init_DownL* ?*init_DownC* ?*init_DownR*))
	)
	
	(min (getF 0 ?*init_UpL* ?*init_UpC* ?*init_UpR* ?*init_MidL* ?*init_MidC* ?*init_MidR* ?*init_DownL* ?*init_DownC* ?*init_DownR*))
	(if (= ?*DEBUG* 1)
        (printout t crlf "Init node: " crlf
        "ID=1 " "Depth=0 " "F=" (getF 0 ?*init_UpL* ?*init_UpC* ?*init_UpR* ?*init_MidL* ?*init_MidC* ?*init_MidR* ?*init_DownL* ?*init_DownC* ?*init_DownR*) " Parent=0 " crlf
        ?*init_UpL* " " ?*init_UpC* " " ?*init_UpR* crlf
		?*init_MidL* " " ?*init_MidC* " " ?*init_MidR* crlf
		?*init_DownL* " " ?*init_DownC* " " ?*init_DownR* crlf
		"====="crlf
		)
	)
)

;; ======================================
;; Вывод найденного решения
;; ======================================
(defrule result
	(declare (salience 500))

	?container <-	(Node (id ?v_id) 
				(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
				(ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
				(DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
				(depth ?v_g) (status ~2) (parent ?v_parent) (f ?v_f)
				)
	(test (= ?v_UL ?*result_UpL*))
	(test (= ?v_UC ?*result_UpC*))
	(test (= ?v_UR ?*result_UpR*))
	(test (= ?v_ML ?*result_MidL*))
	(test (= ?v_MC ?*result_MidC*))
	(test (= ?v_MR ?*result_MidR*))
	(test (= ?v_DL ?*result_DownL*))
	(test (= ?v_DC ?*result_DownC*))
	(test (= ?v_DR ?*result_DownR*))
=>
	(modify ?container(status 2))
	
	(printout t crlf "==================================================" crlf
	"Result path: " crlf
	"ID=" ?v_id  " Depth=" ?v_g " F=" ?v_f " Parent=" ?v_parent crlf
		?v_UL " " ?v_UC " " ?v_UR crlf
		?v_ML " " ?v_MC " " ?v_MR crlf
		?v_DL " " ?v_DC " " ?v_DR crlf
	)
)

;; ======================================
;; Случай если решения не найдено
;; ======================================
(defrule stop_if_no_solution
	(declare (salience 200))

	(not (Node(status 0|2)))
=>
	(halt)
	(printout t crlf "Solution not finded." crlf)
)

;; ======================================
;; Случай если решения найдено, остановливаем программу
;; ======================================
(defrule stop_if_solution_finded
	(declare (salience 200))

	(Node(status 2))
=>
	(halt)
	(printout t crlf "Solution finded! " crlf)
	(printout t "Nodes created: " ?*NODES_CREATED* crlf)
	(printout t "Steps passed: " ?*STEPS_PASSED* crlf)
)

;; ======================================
;; Случай если не было найдено минимума
;; ======================================
(defrule fix_min
	(declare (salience 175))
	?f_addr_min <- (min ?min)
	(not (exists (Node (f ?F&:(<= ?F ?min)) (status 0))))
=>
	(retract ?f_addr_min)
	(assert (min (+ ?min 1)))
)

;; ======================================
;; Определение текущего минимума ЦФ
;; ======================================
(defrule find_min
	(declare (salience 150))

	?f_addr_min <- (min ?min)
	(Node (f ?F&:(< ?F ?min)) (status 0))
=>
	(retract ?f_addr_min)
	(assert (min ?F))
)

;; ======================================
;; Функция удаления повторяющихся вершин
;; ======================================
(defrule remove_repeats
	(declare (salience 1000)); максимальный приоритет

	?f_addr_1 <-(Node (id ?v_id_1) 
					(UL ?v_UL_1) (UC ?v_UC_1) (UR ?v_UR_1)
					(ML ?v_ML_1) (MC ?v_MC_1) (MR ?v_MR_1)
					(DL ?v_DL_1) (DC ?v_DC_1) (DR ?v_DR_1)
					(depth ?v_g_1) (status 1) (parent ?v_parent_1) (f ?v_f_1)
				)

	?f_addr_2 <-(Node (id ?v_id_2&~?v_id_1)
					(UL ?v_UL_2&:(= ?v_UL_1 ?v_UL_2)) (UC ?v_UC_2&:(= ?v_UC_1 ?v_UC_2)) (UR ?v_UR_2&:(= ?v_UR_1 ?v_UR_2))
					(ML ?v_ML_2&:(= ?v_ML_1 ?v_ML_2)) (MC ?v_MC_2&:(= ?v_MC_1 ?v_MC_2)) (MR ?v_MR_2&:(= ?v_MR_1 ?v_MR_2))
					(DL ?v_DL_2&:(= ?v_DL_1 ?v_DL_2)) (DC ?v_DC_2&:(= ?v_DC_1 ?v_DC_2)) (DR ?v_DR_2&:(= ?v_DR_1 ?v_DR_2))
					(depth ?v_g_2) (status 0) (parent ?v_parent_2) (f ?v_f_2)
				)
=>
	(if (= ?*DEBUG* 1) then
		(printout t crlf "Deleting repeat node:" crlf)
		(printout t "ID=" ?v_id_2  " Depth=" ?v_g_2 " F=" ?v_f_2 " Parent=" ?v_parent_2 crlf
            ?v_UL_2 " " ?v_UC_2 " " ?v_UR_2 crlf
            ?v_ML_2 " " ?v_MC_2 " " ?v_MR_2 crlf
            ?v_DL_2 " " ?v_DC_2 " " ?v_DR_2 crlf
			"=====" crlf
		)
	)
	(if (<= ?v_f_1 ?v_f_2) then
			(retract ?f_addr_2)
			(if (= ?*DEBUG* 1) then (printout t "Deleting repeat node..." crlf))
	else
			(modify ?f_addr_1 (parent ?v_parent_2) (depth ?v_g_2) (f ?v_f_2))
			(retract ?f_addr_2)
			(if (= ?*DEBUG* 1) then (printout t "Deleting and refreshing prev repeat" crlf))
	)
	(bind ?*NODES_CREATED* (- ?*NODES_CREATED* 1))
)

;; ======================================
;; Функция вывода результирующего конечного путя
;; ======================================
(defrule show_answer
	(declare (salience 500))

	(Node (id ?v_id) (status 2) (parent ?v_pid))
	?container <- (Node(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
                    (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
                    (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
					(id ?v_pid) (status ~2) (parent ?v_parent) (depth ?v_g) (f ?v_f))
=>
	(modify ?container(status 2))
	(printout t "ID=" ?v_pid  " Depth=" ?v_g " F=" ?v_f " Parent=" ?v_parent crlf
            ?v_UL " " ?v_UC " " ?v_UR crlf
            ?v_ML " " ?v_MC " " ?v_MR crlf
            ?v_DL " " ?v_DC " " ?v_DR crlf
	)
)

;; ======================================
;; Функция удаления вершин у которых статус не соотвествует 2 (решению)
;; ======================================
(defrule delete_not_answer
	(declare (salience 400))
	(Node(status 2))
	?container <- (Node(status ~2))
=>
	(retract ?container);
)

;; ======================================
;; Создание новых вершин/всевозможное перемещение "0"
;; ======================================
(defrule create_UpperLeft
	(declare (salience 100))
	?f_addr_min <- (min ?min)

	?f_addr_node <- (Node (id ?v_id) 
					(UL     0) (UC ?v_UC) (UR ?v_UR)
                    (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
                    (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
					(depth ?v_g) (status 0) (parent ?v_parent)
					(f ?v_f&:(= ?v_f ?min))
					)
=>
	(if (= ?*DEBUG* 1) then (printout t crlf "Creating 2 new node from node: " crlf "Id=" ?v_id  " Depth=" ?v_g " F=" ?v_f " Parent=" ?v_parent crlf
							(fact-slot-value ?f_addr_node UL) " " (fact-slot-value ?f_addr_node UC) " " (fact-slot-value ?f_addr_node UR) crlf
							(fact-slot-value ?f_addr_node ML) " " (fact-slot-value ?f_addr_node MC) " " (fact-slot-value ?f_addr_node MR) crlf
							(fact-slot-value ?f_addr_node DL) " " (fact-slot-value ?f_addr_node DC) " " (fact-slot-value ?f_addr_node DR) crlf
							"====="crlf
							)
	)

	(modify ?f_addr_node(status 1))

	(bind ?a1 (getF (+ ?v_g 1) ?v_UC 0 ?v_UR ?v_ML ?v_MC ?v_MR ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UC) (UC 0    ) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a1)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UC " 0 " ?v_UR crlf
							?v_ML " " ?v_MC " " ?v_MR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)
	
	(bind ?a2 (getF (+ ?v_g 1) ?v_ML ?v_UC ?v_UR 0 ?v_MC ?v_MR ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_ML) (UC ?v_UC) (UR ?v_UR)
            (ML     0) (MC ?v_MC) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a2)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_ML " " ?v_UC " " ?v_UR crlf
							"0 " ?v_MC " " ?v_MR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?*NODES_CREATED* (+ ?*NODES_CREATED* 2))
	(bind ?*STEPS_PASSED* (+ ?*STEPS_PASSED* 1))
)

(defrule create_UpperCenter
	(declare (salience 100))
	?f_addr_min <- (min ?min)

	?f_addr_node <- (Node (id ?v_id) 
					(UL ?v_UL) (UC     0) (UR ?v_UR)
                    (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
                    (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
					(depth ?v_g) (status 0) (parent ?v_parent) 
					(f ?v_f&:(= ?v_f ?min))
					)
=>
	(if (= ?*DEBUG* 1) then (printout t crlf "Creating 3 new node from node: " crlf "Id=" ?v_id  " Depth=" ?v_g " F=" ?v_f " Parent=" ?v_parent crlf
							(fact-slot-value ?f_addr_node UL) " " (fact-slot-value ?f_addr_node UC) " " (fact-slot-value ?f_addr_node UR) crlf
							(fact-slot-value ?f_addr_node ML) " " (fact-slot-value ?f_addr_node MC) " " (fact-slot-value ?f_addr_node MR) crlf
							(fact-slot-value ?f_addr_node DL) " " (fact-slot-value ?f_addr_node DC) " " (fact-slot-value ?f_addr_node DR) crlf
							"====="crlf
							)
	)

	(modify ?f_addr_node(status 1))

	(bind ?a1 (getF (+ ?v_g 1) 0 ?v_UL ?v_UR ?v_ML ?v_MC ?v_MR ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL     0) (UC ?v_UL) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a1)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							"0 " ?v_UL " " ?v_UR crlf
							?v_ML " " ?v_MC " " ?v_MR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)
	
	(bind ?a2 (getF (+ ?v_g 1) ?v_UL ?v_MC ?v_UR ?v_ML 0 ?v_MR ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_MC) (UR ?v_UR)
            (ML ?v_ML) (MC     0) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a2)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_MC " " ?v_UR crlf
							?v_ML " 0 " ?v_MR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?a3 (getF (+ ?v_g 1) ?v_UL ?v_UR 0 ?v_ML ?v_MC ?v_MR ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UR) (UR     0)
            (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a3)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UR " 0" crlf
							?v_ML " " ?v_MC " " ?v_MR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?*NODES_CREATED* (+ ?*NODES_CREATED* 3))
	(bind ?*STEPS_PASSED* (+ ?*STEPS_PASSED* 1))
)

(defrule create_UpperRight
	(declare (salience 100))
	?f_addr_min <- (min ?min)

	?f_addr_node <- (Node (id ?v_id) 
					(UL ?v_UL) (UC ?v_UC) (UR     0)
                    (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
                    (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
					(depth ?v_g) (status 0) (parent ?v_parent) 
					(f ?v_f&:(= ?v_f ?min))
					)
=>
	(if (= ?*DEBUG* 1) then (printout t crlf "Creating 2 new node from node: " crlf "Id=" ?v_id  " Depth=" ?v_g " F=" ?v_f " Parent=" ?v_parent crlf
							(fact-slot-value ?f_addr_node UL) " " (fact-slot-value ?f_addr_node UC) " " (fact-slot-value ?f_addr_node UR) crlf
							(fact-slot-value ?f_addr_node ML) " " (fact-slot-value ?f_addr_node MC) " " (fact-slot-value ?f_addr_node MR) crlf
							(fact-slot-value ?f_addr_node DL) " " (fact-slot-value ?f_addr_node DC) " " (fact-slot-value ?f_addr_node DR) crlf
							"====="crlf
							)
	)

	(modify ?f_addr_node(status 1))

	(bind ?a1 (getF (+ ?v_g 1) ?v_UL 0 ?v_UC ?v_ML ?v_MC ?v_MR ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC     0) (UR ?v_UC)
            (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a1)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " 0 " ?v_UC crlf
							?v_ML " " ?v_MC " " ?v_MR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?a2 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_MR ?v_ML ?v_MC 0 ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_MR)
            (ML ?v_ML) (MC ?v_MC) (MR     0)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a2)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_MR crlf
							?v_ML " " ?v_MC " 0" crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?*NODES_CREATED* (+ ?*NODES_CREATED* 2))
	(bind ?*STEPS_PASSED* (+ ?*STEPS_PASSED* 1))
)

(defrule create_MiddleLeft
	(declare (salience 100))
	?f_addr_min <- (min ?min)

	?f_addr_node <- (Node (id ?v_id) 
					(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
                    (ML     0) (MC ?v_MC) (MR ?v_MR)
                    (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
					(depth ?v_g) (status 0) (parent ?v_parent) 
					(f ?v_f&:(= ?v_f ?min))
					)
=>
	(if (= ?*DEBUG* 1) then (printout t crlf "Creating 3 new node from node: " crlf "Id=" ?v_id  " Depth=" ?v_g " F=" ?v_f " Parent=" ?v_parent crlf
							(fact-slot-value ?f_addr_node UL) " " (fact-slot-value ?f_addr_node UC) " " (fact-slot-value ?f_addr_node UR) crlf
							(fact-slot-value ?f_addr_node ML) " " (fact-slot-value ?f_addr_node MC) " " (fact-slot-value ?f_addr_node MR) crlf
							(fact-slot-value ?f_addr_node DL) " " (fact-slot-value ?f_addr_node DC) " " (fact-slot-value ?f_addr_node DR) crlf
							"====="crlf
							)
	)

	(modify ?f_addr_node(status 1))

	(bind ?a1 (getF (+ ?v_g 1) 0 ?v_UC ?v_UR ?v_UL ?v_MC ?v_MR ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL     0) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_UL) (MC ?v_MC) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a1)
        )
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							"0 " ?v_UC " " ?v_UR crlf
							?v_UL " " ?v_MC " " ?v_MR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?a2 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_MC 0 ?v_MR ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_MC) (MC     0) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a2)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_MC " 0 " ?v_MR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?a3 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_DL ?v_MC ?v_MR 0 ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_DL) (MC ?v_MC) (MR ?v_MR)
            (DL     0) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a3)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_DL " " ?v_MC " " ?v_MR crlf
							"0 " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?*NODES_CREATED* (+ ?*NODES_CREATED* 3))
	(bind ?*STEPS_PASSED* (+ ?*STEPS_PASSED* 1))
)

(defrule create_MiddleCenter
	(declare (salience 100))
	?f_addr_min <- (min ?min)

	?f_addr_node <- (Node (id ?v_id) 
					(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
                    (ML ?v_ML) (MC     0) (MR ?v_MR)
                    (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
					(depth ?v_g) (status 0) (parent ?v_parent) 
					(f ?v_f&:(= ?v_f ?min))
					)
=>
	(if (= ?*DEBUG* 1) then (printout t crlf "Creating 4 new node from node: " crlf "Id=" ?v_id  " Depth=" ?v_g " f=" ?v_f " Parent=" ?v_parent crlf
							(fact-slot-value ?f_addr_node UL) " " (fact-slot-value ?f_addr_node UC) " " (fact-slot-value ?f_addr_node UR) crlf
							(fact-slot-value ?f_addr_node ML) " " (fact-slot-value ?f_addr_node MC) " " (fact-slot-value ?f_addr_node MR) crlf
							(fact-slot-value ?f_addr_node DL) " " (fact-slot-value ?f_addr_node DC) " " (fact-slot-value ?f_addr_node DR) crlf
							"====="crlf
							)
	)

	(modify ?f_addr_node(status 1))

	(bind ?a1 (getF (+ ?v_g 1) ?v_UL 0 ?v_UR ?v_ML ?v_UC ?v_MR ?v_DL ?v_DC ?v_DR))
	(retract ?f_addr_min)
	(assert (min ?a1))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC     0) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_UC) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a1)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " 0 " ?v_UR crlf
							?v_ML " " ?v_UC " " ?v_MR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?a2 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR 0 ?v_ML ?v_MR ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML     0) (MC ?v_ML) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a2)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							"0 " ?v_ML " " ?v_MR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?a3 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_ML ?v_MR 0 ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_MR) (MR     0)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a3)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_ML " " ?v_MR " 0" crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?a4 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_ML ?v_DC ?v_MR ?v_DL 0 ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_DC) (MR ?v_MR)
            (DL ?v_DL) (DC     0) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a4)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_ML " " ?v_DC " " ?v_MR crlf
							?v_DL " 0 " ?v_DR crlf
							)
	)

	(bind ?*NODES_CREATED* (+ ?*NODES_CREATED* 4))
	(bind ?*STEPS_PASSED* (+ ?*STEPS_PASSED* 1))
)

(defrule create_MiddleRight
	(declare (salience 100))
	?f_addr_min <- (min ?min)

	?f_addr_node <- (Node (id ?v_id) 
					(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
                    (ML ?v_ML) (MC ?v_MC) (MR     0)
                    (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
					(depth ?v_g) (status 0) (parent ?v_parent) 
					(f ?v_f&:(= ?v_f ?min))
					)
=>
	(if (= ?*DEBUG* 1) then (printout t crlf "Creating 3 new node from node: " crlf "Id=" ?v_id  " Depth=" ?v_g " f=" ?v_f " Parent=" ?v_parent crlf
							(fact-slot-value ?f_addr_node UL) " " (fact-slot-value ?f_addr_node UC) " " (fact-slot-value ?f_addr_node UR) crlf
							(fact-slot-value ?f_addr_node ML) " " (fact-slot-value ?f_addr_node MC) " " (fact-slot-value ?f_addr_node MR) crlf
							(fact-slot-value ?f_addr_node DL) " " (fact-slot-value ?f_addr_node DC) " " (fact-slot-value ?f_addr_node DR) crlf
							"====="crlf
							)
	)

	(modify ?f_addr_node(status 1))

	(bind ?a1 (getF (+ ?v_g 1) ?v_UL ?v_UC 0 ?v_ML ?v_MC ?v_UR ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR     0)
            (ML ?v_ML) (MC ?v_MC) (MR ?v_UR)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a1)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " 0" crlf
							?v_ML " " ?v_MC " " ?v_UR crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?a2 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_ML 0 ?v_MC ?v_DL ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_ML) (MC     0) (MR ?v_MC)
            (DL ?v_DL) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a2)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_ML " 0 " ?v_MC crlf
							?v_DL " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?a3 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_ML ?v_MC ?v_DR ?v_DL ?v_DC 0))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_MC) (MR ?v_DR)
            (DL ?v_DL) (DC ?v_DC) (DR     0)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a3)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_ML " " ?v_MC " " ?v_DR crlf
							?v_DL " " ?v_DC " 0" crlf
							)
	)

	(bind ?*NODES_CREATED* (+ ?*NODES_CREATED* 3))
	(bind ?*STEPS_PASSED* (+ ?*STEPS_PASSED* 1))
)

(defrule create_DownLeft
	(declare (salience 100))
	?f_addr_min <- (min ?min)

	?f_addr_node <- (Node (id ?v_id) 
					(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
                    (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
                    (DL     0) (DC ?v_DC) (DR ?v_DR)
					(depth ?v_g) (status 0) (parent ?v_parent) 
					(f ?v_f&:(= ?v_f ?min))
					)
=>
	(if (= ?*DEBUG* 1) then (printout t crlf "Creating 2 new node from node: " crlf "Id=" ?v_id  " Depth=" ?v_g " F=" ?v_f " Parent=" ?v_parent crlf
							(fact-slot-value ?f_addr_node UL) " " (fact-slot-value ?f_addr_node UC) " " (fact-slot-value ?f_addr_node UR) crlf
							(fact-slot-value ?f_addr_node ML) " " (fact-slot-value ?f_addr_node MC) " " (fact-slot-value ?f_addr_node MR) crlf
							(fact-slot-value ?f_addr_node DL) " " (fact-slot-value ?f_addr_node DC) " " (fact-slot-value ?f_addr_node DR) crlf
							"====="crlf
							)
	)

	(modify ?f_addr_node(status 1))

	(bind ?a1 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR 0 ?v_MC ?v_MR ?v_ML ?v_DC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML     0) (MC ?v_MC) (MR ?v_MR)
            (DL ?v_ML) (DC ?v_DC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a1)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							"0 " ?v_MC " " ?v_MR crlf
							?v_ML " " ?v_DC " " ?v_DR crlf
							)
	)

	(bind ?a2 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_ML ?v_MC ?v_MR ?v_DC 0 ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
            (DL ?v_DC) (DC     0) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a2)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_ML " " ?v_MC " " ?v_MR crlf
							?v_DC " 0 " ?v_DR crlf
							)
	)

	(bind ?*NODES_CREATED* (+ ?*NODES_CREATED* 2))
	(bind ?*STEPS_PASSED* (+ ?*STEPS_PASSED* 1))
)

(defrule create_DownCenter
	(declare (salience 100))
	?f_addr_min <- (min ?min)

	?f_addr_node <- (Node (id ?v_id) 
					(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
                    (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
                    (DL ?v_DL) (DC     0) (DR ?v_DR)
					(depth ?v_g) (status 0) (parent ?v_parent) 
					(f ?v_f&:(= ?v_f ?min))
					)
=>
	(if (= ?*DEBUG* 1) then (printout t crlf "Creating 3 new node from node: " crlf "Id=" ?v_id  " Depth=" ?v_g " F=" ?v_f " Parent=" ?v_parent crlf
							(fact-slot-value ?f_addr_node UL) " " (fact-slot-value ?f_addr_node UC) " " (fact-slot-value ?f_addr_node UR) crlf
							(fact-slot-value ?f_addr_node ML) " " (fact-slot-value ?f_addr_node MC) " " (fact-slot-value ?f_addr_node MR) crlf
							(fact-slot-value ?f_addr_node DL) " " (fact-slot-value ?f_addr_node DC) " " (fact-slot-value ?f_addr_node DR) crlf
							"====="crlf
							)
	)

	(modify ?f_addr_node(status 1))

	(bind ?a1 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_ML 0 ?v_MR ?v_DL ?v_MC ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_ML) (MC     0) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_MC) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a1)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_ML " 0 " ?v_MR crlf
							?v_DL " " ?v_MC " " ?v_DR crlf
							)
	)

	(bind ?a2 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_ML ?v_MC ?v_MR 0 ?v_DL ?v_DR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
            (DL     0) (DC ?v_DL) (DR ?v_DR)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a2)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_ML " " ?v_MC " " ?v_MR crlf
							"0 " ?v_DL " " ?v_DR crlf
							)
	)

	(bind ?a3 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_ML ?v_MC ?v_MR ?v_DL ?v_DR 0))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
            (DL ?v_DL) (DC ?v_DR) (DR     0)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a3)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_ML " " ?v_MC " " ?v_MR crlf
							?v_DL " " ?v_DR " 0" crlf
							)
	)

	(bind ?*NODES_CREATED* (+ ?*NODES_CREATED* 3))
	(bind ?*STEPS_PASSED* (+ ?*STEPS_PASSED* 1))
)

(defrule create_DownRight
	(declare (salience 100))
	?f_addr_min <- (min ?min)

	?f_addr_node <- (Node (id ?v_id) 
					(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
                    (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
                    (DL ?v_DL) (DC ?v_DC) (DR     0)
					(depth ?v_g) (status 0) (parent ?v_parent) 
					(f ?v_f&:(= ?v_f ?min))
					)
=>
	(if (= ?*DEBUG* 1) then (printout t crlf "Creating 2 new node from node: " crlf "Id=" ?v_id  " Depth=" ?v_g " F=" ?v_f " Parent=" ?v_parent crlf
							(fact-slot-value ?f_addr_node UL) " " (fact-slot-value ?f_addr_node UC) " " (fact-slot-value ?f_addr_node UR) crlf
							(fact-slot-value ?f_addr_node ML) " " (fact-slot-value ?f_addr_node MC) " " (fact-slot-value ?f_addr_node MR) crlf
							(fact-slot-value ?f_addr_node DL) " " (fact-slot-value ?f_addr_node DC) " " (fact-slot-value ?f_addr_node DR) crlf
							"====="crlf
							)
	)

	(modify ?f_addr_node(status 1))

	(bind ?a1 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_ML ?v_MC 0 ?v_DL ?v_DC ?v_MR))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_MC) (MR     0)
			(DL ?v_DL) (DC ?v_DC) (DR ?v_MR)
			(depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a1)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_ML " " ?v_MC " 0" crlf
							?v_DL " " ?v_DC " " ?v_MR crlf
							)
	)
	(bind ?a2 (getF (+ ?v_g 1) ?v_UL ?v_UC ?v_UR ?v_ML ?v_MC ?v_MR ?v_DL 0 ?v_DC))
	(assert (Node (id (setID)) 
			(UL ?v_UL) (UC ?v_UC) (UR ?v_UR)
            (ML ?v_ML) (MC ?v_MC) (MR ?v_MR)
            (DL ?v_DL) (DC     0) (DR ?v_DC)
            (depth (+ ?v_g 1)) (status 0) (parent ?v_id) (f ?a2)
			)
	)
	(if (= ?*DEBUG* 1) then (printout t "To uncover:" crlf
							?v_UL " " ?v_UC " " ?v_UR crlf
							?v_ML " " ?v_MC " " ?v_MR crlf
							?v_DL " 0 " ?v_DC crlf
							)
	)

	(bind ?*NODES_CREATED* (+ ?*NODES_CREATED* 2))
	(bind ?*STEPS_PASSED* (+ ?*STEPS_PASSED* 1))
)