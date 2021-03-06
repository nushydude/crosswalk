
package org.xwalk.core.internal;

import android.content.Context;
import android.view.ActionMode;
import android.view.Menu;
import android.view.MenuItem;

import org.chromium.content_public.browser.ActionModeCallbackHelper;

public class XWalkActionModeCallback implements ActionMode.Callback {
    private final Context mContext;
    private final XWalkContent mXwalkContent;
    private final ActionModeCallbackHelper mHelper;
    private int mAllowedMenuItems;

    public XWalkActionModeCallback(Context context, XWalkContent content,
            ActionModeCallbackHelper helper) {
        mContext = context;
        mXwalkContent = content;
        mHelper = helper;
        mHelper.setAllowedMenuItems(0); // No item is allowed by default for WebView.
    }

    @Override
    public boolean onCreateActionMode(ActionMode mode, Menu menu) {
        // TODO (iotto): Make selection configurable
        int allowedItems = ActionModeCallbackHelper.MENU_ITEM_PROCESS_TEXT
                | ActionModeCallbackHelper.MENU_ITEM_SHARE;
        // int allowedItems = (getAllowedMenu(ActionModeCallbackHelper.MENU_ITEM_SHARE)
        // | getAllowedMenu(ActionModeCallbackHelper.MENU_ITEM_WEB_SEARCH)
        // | getAllowedMenu(ActionModeCallbackHelper.MENU_ITEM_PROCESS_TEXT));
        if (allowedItems != mAllowedMenuItems) {
            mHelper.setAllowedMenuItems(allowedItems);
            mAllowedMenuItems = allowedItems;
        }
        mHelper.onCreateActionMode(mode, menu);
        return true;
    }

    // private int getAllowedMenu(int menuItem) {
    // boolean showItem = true;
    // if (menuItem == ActionModeCallbackHelper.MENU_ITEM_WEB_SEARCH) {
    // showItem = isWebSearchAvailable();
    // }
    // return showItem && mAwContents.isSelectActionModeAllowed(menuItem) ? menuItem : 0;
    // }

    @Override
    public void onDestroyActionMode(ActionMode arg0) {
        mHelper.onDestroyActionMode();
    }

    @Override
    public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
        return mHelper.onPrepareActionMode(mode, menu);
    }

    @Override
    public boolean onActionItemClicked(ActionMode mode, MenuItem item) {
        if (!mHelper.isActionModeValid())
            return true;

        return mHelper.onActionItemClicked(mode, item);
    }
}
