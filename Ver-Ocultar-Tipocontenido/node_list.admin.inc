<?php
/*
 * Add checkbox to the content type formulary
 */
function node_list_form_alter(&$form, &$form_state, $form_id) {
	if ($form_id == 'node_type_form') {
		$type = $form['#node_type']->type; //capture the node type for next search
		
		//Search for the option in the custon node list
		$result = db_query('SELECT * FROM node_list_table WHERE node_type = :ntype', array(':ntype' => $type));
		$exist = 1;
		if(!$result->fetchAssoc()){
			$exist = 0;
		}
		
		//We create the element with his actual value
  		$form['checkbox'] = array(
			'#type' => 'checkbox',
			'#title' => t('Check for show this content on "Node list module".'),
			'#default_value' => $exist,
			'#checked' => $exist,
		);
   	 	$form['#submit'][] = 'node_list_submit';
	}
}

/*
 * Function for save the checkbox value
 */
function node_list_submit($form, &$form_state){
	$type = $form['#node_type']->type;
	//If checked
	if($form['checkbox']['#checked'] == 1){
		//Check if the value already exist in the table
		$result = db_query('SELECT * FROM node_list_table WHERE node_type = :ntype', array(':ntype' => $type));
		
		//If doesnt exist, set value into the table
		if(!$result->fetchAssoc()){
			db_insert('node_list_table')->fields(array(
  				'node_type' => $form['#node_type']->type,
			))->execute();
		}
	}
	//If not checked
	else{
		db_delete('node_list_table')
  		->condition('node_type', $type)
  		->execute();
	}
}
?>