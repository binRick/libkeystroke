/**********************************/
list_t *downkeys;
list_t *downkeys_history;


/**********************************/


int load_keybindings(char *file_path){
//json_t json;
//json_load_file(&json, file_path);
//json_unload(&json);
}


char * get_downkeys(){
  list_node_t         *node;
  list_iterator_t     *it = list_iterator_new(downkeys, LIST_HEAD);
  int                 i   = 0;
  struct StringBuffer *sb = stringbuffer_new_with_options(1024, true);

  while ((node = list_iterator_next(it))) {
    struct DownKey *DK = (struct DownKey *)node->val;
    stringbuffer_append_string(sb, " ");
    stringbuffer_append_int(sb, DK->keycode);
    i++;
  }
  list_iterator_destroy(it);
  char *ret = strdup(stringbuffer_to_string(sb));

  stringbuffer_release(sb);
  return(ret);
}


bool keycode_is_down(int keycode){
  list_node_t     *node;
  list_iterator_t *it = list_iterator_new(downkeys, LIST_HEAD);
  bool            ret = false;
  int             i   = 0;

  while ((node = list_iterator_next(it))) {
    struct DownKey *DK = (struct DownKey *)node->val;
    if (DK->keycode == keycode) {
      ret = true;
      break;
    }
    i++;
  }
  list_iterator_destroy(it);
  return(ret);
}


void set_keycode_is_up(int keycode){
  list_node_t     *node;
  list_iterator_t *it = list_iterator_new(downkeys, LIST_HEAD);
  int             i   = 0;

  while ((node = list_iterator_next(it))) {
    struct DownKey *DK = (struct DownKey *)node->val;
    if (DK->keycode == keycode) {
      list_remove(downkeys, node);
    }
    i++;
  }
  list_iterator_destroy(it);


  return;
}


char * get_downkeys_strs(){
  list_node_t         *node;
  list_iterator_t     *it = list_iterator_new(downkeys, LIST_HEAD);
  int                 i   = 0;
  struct StringBuffer *sb = stringbuffer_new_with_options(1024, true);

  while ((node = list_iterator_next(it))) {
    struct DownKey *DK = (struct DownKey *)node->val;
    stringbuffer_append_string(sb, " ");
    stringbuffer_append_string(sb, convertKeyCode(DK->keycode));
    i++;
  }
  list_iterator_destroy(it);
  char *ret = strdup(stringbuffer_to_string(sb));

  stringbuffer_release(sb);
  return(ret);
}


void set_keycode_is_down(int keycode){
  if (keycode_is_down(keycode)) {
    return;
  }
  struct DownKey *KC = malloc(sizeof(struct DownKey));

  KC->keycode = keycode;
  KC->ts      = timestamp();
  list_rpush(downkeys, list_node_new(KC));
  list_rpush(downkeys_history, list_node_new(KC));
}


char * keycode_is_down_str(int keycode){
  bool is_down = keycode_is_down(keycode);

  return((is_down) ? "Yes" : "No");
}


int down_keycodes_qty(){
  list_node_t     *node;
  list_iterator_t *it = list_iterator_new(downkeys, LIST_HEAD);
  int             i   = 0;

  while ((node = list_iterator_next(it))) {
    i++;
  }
  list_iterator_destroy(it);


  return(i);
}


void set_keycode_state(int keycode, bool is_down){
  if (is_down) {
    set_keycode_is_down(keycode);
  }else{
    set_keycode_is_up(keycode);
  }
}


char *get_key_with_downkeys(char *key){
  struct StringBuffer *sb = stringbuffer_new_with_options(1024, true);

  stringbuffer_append_string(sb, key);
  stringbuffer_append_string(sb, " ");
  stringbuffer_append_string(sb, get_downkeys_strs());

  char *ret = strdup(stringbuffer_to_string(sb));

  stringbuffer_release(sb);
  return(ret);
}

